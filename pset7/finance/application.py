import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Invalid Stock Symbol")

        elif not request.form.get("shares"):
            return apology("Missing Shares")

        symbol = request.form.get("symbol").upper()

        #Lookup in api
        quote = lookup(symbol)

        #Checking if lookup failed
        if quote == None:
            return apology("Invalid Symbol")

        #Check if user has sufficient funds in DB
        cashier = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        cash = cashier[0]["cash"]

        price = quote["price"]
        shares = int(request.form.get("shares"))
        updated_cash = cash - shares * price

        if updated_cash < 0:
            return apology("You dont have enough Dough")

        #Add share and update cash amount
        db.execute("UPDATE users SET cash = :updated_cash WHERE id = :id", id=session["user_id"], updated_cash=updated_cash)

        #Update user Portfolio
        rows = db.execute("SELECT * FROM portfolios WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)
        #Insert new row if no shares exist for that Symbol
        if len(rows == 0):
            db.execute("INSERT INTO portfolios (id, symbol, shares) VALUES(:id, :symbol, :shares)",
                        id=session["user_id"], symbol=symbol, shares=shares)
        else:
            db.execute("UPDATE portfolios SET shares = shares + :shares WHERE id = :id", id=session["user_id"], shares=shares)

        #Update History
        db.execute("INSERT INTO history (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)",
                        id=session["user_id"], symbol=symbol, shares=shares, price=price)

        return render_template("index.html")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        #Ensure quote was entered
        if not request.form.get("symbol"):
            return apology("Please enter a Stock Symbol")

        #Storing entered Symbol/ Get symbol and make uppercase
        symbol = request.form.get("symbol").upper()

        #Lookup in api
        quote = lookup(symbol)

        #Checking if lookup failed
        if quote == None:
            return apology("Invalid Symbol")

        return render_template("quoted.html", name=quote["name"], symbol=symbol, price=quote["price"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        #Ensure User was submitted
        if not request.form.get("username"):
            return apology("Please provide a Username")

        #Ensure Password is provided
        elif not request.form.get("password"):
            return apology("Please provide a Password")
        elif not request.form.get("repeat-password"):
            return apology("Please provide the Password Again")
        #Ensure both Passwords are the same
        elif request.form.get("repeat-password") != request.form.get("password"):
            return apology("The Password did not match")

        #Store users in the Database
        #example "INSERT INTO users (username, hash) VALUES (:username, :hash)"
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                          username=request.form.get("username"),
                          hash=generate_password_hash(request.form.get("password")))

        #If User already exist
        if not result:
            return apology("Username aleady Exist")

        #Query Database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Invalid Stock Symbol")

        elif not request.form.get("shares"):
            return apology("Missing Shares")

        symbol = request.form.get("symbol").upper()

        #Lookup in api
        quote = lookup(symbol)

        #Checking if lookup failed
        if quote == None:
            return apology("Invalid Symbol")

        #Number of Shares selected
        shares = int(request.form.get("shares"))

        #Checking if user has share
        shares_current_list = db.execute("SELECT shares FROM portfolios WHERE id=:id AND symbol=:symbol", id=session["user_id"], symbol=symbol)
        if len(shares_current_list) == 0:
            apology("Symbol is not owned")
        shares_current = shares_current_list[0]["shares"]
        updated_shares = shares - shares_current
        if (updated_shares < 0):
            apology("Too many shares")

        #Price of share
        price = quote["price"]
        #Cash Increase after selling
        cash_increase = price * shares;

        #Update cash from users table
        db.execute("UPDATE users WHERE id = :id SET cash=cash+:cash_increase WHERE id=:id", id=session["user_id"], cash_increase=cash_increase)

        #Update Portfolios
        if updated_shares == 0:
            db.execute("DELETE FROM portfolios WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=symbol)

        elif updated_shares > 0:
            db.execute("UPDATE FROM portfolios WHERE id = :id SET shares = :updated_shares", id=session["user_id"], updated_shares=updated_shares)

        #Update History
        db.execute("INSERT INTO history (id, symbol, shares, price) VALUES(:id, :symbol, :shares, :price)",
                        id=session["user_id"], symbol=symbol, shares=shares, price=price)

    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
