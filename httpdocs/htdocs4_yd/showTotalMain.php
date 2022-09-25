<?php
$dataArray = json_decode(file_get_contents("dataTotal.json"), true);

   echo $dataArray['total'];
   

