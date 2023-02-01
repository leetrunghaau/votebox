<?php
$data1 = json_decode(file_get_contents("data1.json"), true);
$data2 = json_decode(file_get_contents("data2.json"), true);
$data3 = json_decode(file_get_contents("data3.json"), true);
$data4 = json_decode(file_get_contents("data4.json"), true);
$dataTotal = json_decode(file_get_contents("datatotal.json"), true);

$dataArray = array(
    'box1' => $data1['value'],
    'box2' => $data2['value'],
    'box3' => $data3['value'],
    'box4' => $data4['value'],
    'errorNum1' => $data1['errorNum'],
    'errorNum2' => $data2['errorNum'],
    'errorNum3' => $data3['errorNum'],
    'errorNum4' => $data4['errorNum'],
    'sethtml1' => $data1['sethtml'],
    'sethtml2' => $data2['sethtml'],
    'sethtml3' => $data3['sethtml'],
    'sethtml4' => $data4['sethtml'],
    'total' => $dataTotal['total']
);
echo json_encode($dataArray);