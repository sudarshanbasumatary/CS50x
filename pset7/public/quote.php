<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            render("apology.php", ["message" => "Empty symbol!"]);
        }
        else
        {
            $stock = lookup(strtoupper($_POST["symbol"]));
            if(empty($stock))
                render("apology.php", ["message" => "Symbol not found!"]);
            else render("quote.php", ["stock" => $stock]);
        }
    }

?>
