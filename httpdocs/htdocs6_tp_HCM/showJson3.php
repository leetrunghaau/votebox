<?php
$dataArray = json_decode(file_get_contents("data3.json"), true);
   echo json_encode($dataArray);
