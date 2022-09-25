<?php
$id = $_GET['id'];
$value = $_GET['value'];
$status = 'false';

if($id == null || $value == null){
    $status = 'false';
}else{
    $dataArray = json_decode(file_get_contents("data.json"), true);
    if($id == 'thung1'){
        if($value + $dataArray['thung1']['errorNum'] <= $dataArray['thung1']['total']){
            $dataArray['thung1']['value'] = (int)$value;
            $status = 'ok';
        }
    }elseif($id == 'thung2'){
        if($value + $dataArray['thung2']['errorNum'] <= $dataArray['thung2']['total']){
            $dataArray['thung2']['value'] = (int)$value;
            $status = 'ok';
        }
    }
    file_put_contents("data.json",json_encode($dataArray));
}
echo $status;
