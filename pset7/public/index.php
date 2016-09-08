<?php

    // configuration
    require("../includes/config.php"); 

    // render portfolio
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"])[0]["cash"];
    
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "title" => "Portfolio"]);

?>
