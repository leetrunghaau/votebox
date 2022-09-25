<?php
$value = $_GET['value'];
$status = 'false';

if ( $value == null) {
    $status = 'false';
} else {

    if ($value == "thung1") {
        $dataArray = json_decode(file_get_contents("data1.json"), true);
        if ($dataArray['sethtml'] == 0) {
            $dataArray['sethtml'] = 1;
        } else {
            $dataArray['sethtml'] = 0;
        }
        $status = 'ok';
        file_put_contents("data1.json", json_encode($dataArray));
    }else if($value == "thung2"){
        $dataArray = json_decode(file_get_contents("data2.json"), true);
        if ($dataArray['sethtml'] == 0) {
            $dataArray['sethtml'] = 1;
        } else {
            $dataArray['sethtml'] = 0;
        }
        $status = 'ok';
        file_put_contents("data2.json", json_encode($dataArray));
    }
}
echo $status;
