<?php
$id = $_GET['id'];

$dataArray = json_decode(file_get_contents("data.json"), true);
if ($id == 'thung1') {
   echo $dataArray['thung1']['value'];
   
} elseif ($id == 'thung2') {
   echo $dataArray['thung2']['value'];
   
}
