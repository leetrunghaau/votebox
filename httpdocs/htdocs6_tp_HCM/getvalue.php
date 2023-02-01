<?php
$id = $_GET['id'];
$value = $_GET['value'];
$status = 'false';

if ($id == null || $value == null) {
    $status = 'false';
} else {


    if ($id == 'thung1') {
        $dataArray = json_decode(file_get_contents("data1.json"), true);

        $dataArray['value'] = (int)$value;
        $status = 'ok';
        file_put_contents("data1.json", json_encode($dataArray));
    } elseif ($id == 'thung2') {
        $dataArray = json_decode(file_get_contents("data2.json"), true);

        $dataArray['value'] = (int)$value;
        $status = 'ok';
        file_put_contents("data2.json", json_encode($dataArray));
    }elseif ($id == 'thung3') {
        $dataArray = json_decode(file_get_contents("data3.json"), true);

        $dataArray['value'] = (int)$value;
        $status = 'ok';
        file_put_contents("data3.json", json_encode($dataArray));
    }
    elseif ($id == 'thung4') {
        $dataArray = json_decode(file_get_contents("data4.json"), true);

        $dataArray['value'] = (int)$value;
        $status = 'ok';
        file_put_contents("data4.json", json_encode($dataArray));
    }

}
echo $status;
