<?php


  //dpm($variables);
?>


<?php foreach( $variables['resultArray'] as $id => $name ){ ?>
    <p><a href="<?php echo $id;?>"><?php echo $name; ?></a><a href="<?php echo $id;?>"><?php echo $name; ?></a></p>
<?php } 


?>