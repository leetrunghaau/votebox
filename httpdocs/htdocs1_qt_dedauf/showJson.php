<?php
$dataArray = json_decode(file_get_contents("data.json"), true);
   echo json_encode($dataArray);
