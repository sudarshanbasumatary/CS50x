<table class="table table-striped">
    <thead>
       <tr>
            <td>Symbol</td>
            <td>Name</td>
            <td>Shares</td>
            <td>Price</td>
            <td>TOTAL</td>
        </tr> 
    </thead>
    
    <tbody>
    <?php foreach ($positions as $position): ?>
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= $position["price"] ?></td>
            <td><?= $position["price"] * $position["shares"] ?></td>
        </tr>
    <?php endforeach ?>
        
        <tr>
            <td>CASH</td>
            <td></td>
            <td></td>
            <td></td>
            <td><?= $cash ?></td>
        </tr>
    </tbody>
</table>