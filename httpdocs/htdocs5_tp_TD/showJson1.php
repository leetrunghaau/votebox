<?php
$dataArray = json_decode(file_get_contents("data1.json"), true);
   echo json_encode($dataArray);
