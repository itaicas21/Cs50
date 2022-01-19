import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    balance = db.execute("SELECT cash FROM users WHERE id == ?",session["user_id"])[0]['cash']
    stocks_held = db.execute("SELECT * FROM stocks_held WHERE user_id == ?",session["user_id"])
    current_prices = []
    projected_sell=0
    for stock in stocks_held:
        current_price = lookup(stock['stock'])['price']
        current_prices.append(current_price)
        projected_sell = projected_sell + current_price*stock['shares']
    return render_template("index.html",stocks_held=stocks_held,current_prices=current_prices,balance=balance,projected_sell=projected_sell)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if not symbol or not shares:
            return apology("Input is blank",400)
        if (shares<0):
            return apology("Only positive integers",400)
        else:
            stock = lookup(symbol)
            if not stock:
                return apology ("Not Found",404)
            balance = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]
            if balance<shares*stock["price"]:
                return apology("Not wealthy enough for so many shares",400)
            else:
                db.execute("INSERT INTO history (stock,shares,price_per_share,transaction_type,inquirer_id) VALUES (?,?,?,?,?)",symbol,shares,stock['price'],"Purchase",session["user_id"])
                db.execute("UPDATE users SET cash = ? WHERE id = ?",balance-shares*stock["price"],session["user_id"])
                query = db.execute("SELECT shares FROM stocks_held WHERE user_id = ? AND stock=?",session["user_id"],symbol)
                print (query)
                if query:
                    db.execute("UPDATE stocks_held SET shares = ? WHERE user_id = ?",query[0]["shares"]+shares,session["user_id"])
                else:
                    db.execute("INSERT INTO stocks_held (user_id,stock,shares) VALUES (?,?,?)",session["user_id"],symbol,shares)
                return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE inquirer_id = ?",session["user_id"])
    print(history)
    return render_template("history.html",history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    if request.method == "POST":
        result = lookup(request.form.get("symbol"))
        if result:
            return render_template("quoted.html",result=result)
        else:
            return apology ("Not Found",404)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        username = request.form.get("username")
        password = request.form.get("password")
        # Check if array is falsy
        if db.execute("SELECT username FROM users WHERE username==?",username):
            return apology("user already exists in db",401)
        else:
            db.execute("INSERT INTO users (username,hash) VALUES (?,?)",username,generate_password_hash(password))
            #Directly log in
            id= db.execute("SELECT id FROM users WHERE username = ?", username)[0]['id']
            session["user_id"] = id
            return redirect("/")
    else:
         return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_to_sell = int(request.form.get("shares"))
        if not symbol or not shares_to_sell:
            return apology("Input is blank",400)
        if (shares_to_sell<0):
            return apology("Only positive integers",400)
        else:
            stock = lookup(symbol)
            if not stock:
                return apology ("Not Found",404)
            shares = db.execute("SELECT shares FROM stocks_held WHERE user_id == ? AND stock == ?", session["user_id"],symbol)[0]["shares"]
            if not shares:
                return apology("You dont have that type of share", 400)
            if shares<shares_to_sell:
                return apology("You're selling more than you have",400)
            balance = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]
            db.execute("UPDATE users SET cash = ? WHERE id = ?",balance+shares_to_sell*stock["price"],session["user_id"])
            if shares==shares_to_sell:
                db.execute("DELETE FROM stocks_held WHERE user_id = ? AND stock = ?",session["user_id"],symbol)
            else:
                db.execute("UPDATE stocks_held SET shares = ? WHERE user_id = ? AND stock = ?", shares-shares_to_sell,session["user_id"],symbol)
            db.execute("INSERT INTO history (stock,shares,price_per_share,transaction_type,inquirer_id) VALUES (?,?,?,?,?)",symbol,shares_to_sell,stock['price'],"Sale",session["user_id"])
            return redirect('/')
    else:
        return render_template("sell.html")
