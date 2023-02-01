<?php
$data = array(
    // 'thung1' => array(
    //     'value' => 45,
    //     'sum' => 100

    // )
    // 'thung2' => array(
    //     'value' => 45,
    //     'sum' => 100
    // ) 
   
        'value' => 45,
        'sum' => 100
    
);
file_put_contents("testdata.json",json_encode($data));