<?php
$value = 0;

$dataArray1 = json_decode(file_get_contents("data1.json"), true);
$dataArray2 = json_decode(file_get_contents("data2.json"), true);

   echo ($dataArray1['value'] + $dataArray1['errorNum'] + $dataArray2['value'] + $dataArray2['errorNum'])*2;
   


   


