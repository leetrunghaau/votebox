<?php
$id = $_GET['id'];
$value = $_GET['value'];
$status = 'false';

if ($id == null || $value == null) {
    $status = 'false';
} else {

    if ($id == 'thung1') {
        $dataArray = json_decode(file_get_contents("data1.json"), true);
        if ($value == 'add') {
            $dataArray['errorNum'] = $dataArray['errorNum'] + 1;
            $status = $dataArray['errorNum'];
            file_put_contents("data1.json", json_encode($dataArray));
        } else if ($value == 'sub') {
            $dataArray['errorNum'] = $dataArray['errorNum'] - 1;
            $status = $dataArray['errorNum'];
            file_put_contents("data1.json", json_encode($dataArray));
        } else if ($value == 'zero') {
            $dataArray['errorNum'] = 0;
            $status = $dataArray['errorNum'];
            file_put_contents("data1.json", json_encode($dataArray));
        }
    } elseif ($id == 'thung2') {
        $dataArray = json_decode(file_get_contents("data2.json"), true);
        if ($value == 'add') {
            $dataArray['errorNum'] = $dataArray['errorNum'] + 1;
            $status = $dataArray['errorNum'];
            file_put_contents("data2.json", json_encode($dataArray));
        } else if ($value == 'sub') {
            $dataArray['errorNum'] = $dataArray['errorNum'] - 1;
            $status = $dataArray['errorNum'];
            file_put_contents("data2.json", json_encode($dataArray));
        } else if ($value == 'zero') {
            $dataArray['errorNum'] = 0;
            $status = $dataArray['errorNum'];
            file_put_contents("data2.json", json_encode($dataArray));
        }
    }
}
echo $status;
