<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        else if (empty($_POST["shares"]))
            apologize("You must specify valid shares");
        else if (preg_match("/^\d+$/", $_POST["shares"]) !== 1)
            apologize("Invalid number of shares.");
        else
        {
            $price = lookup(strtoupper($_POST["symbol"]))["price"];
            $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"])[0]["cash"];
            
            if($price * $_POST["shares"] > $cash)
                apologize("You can't afford that.");
            
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", 
            $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $price * $_POST["shares"], $_SESSION["id"]);
            CS50::query("INSERT INTO history (user_id, transaction, date, symbol, shares, price) VALUES(?, 'Buy', CURRENT_TIMESTAMP, ?, ?, ?)", 
            $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"], $price);
        
            // redirect to portfolio
            redirect("/");
        }
    }

?>
