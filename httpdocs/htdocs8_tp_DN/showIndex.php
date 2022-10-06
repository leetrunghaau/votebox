<?php
$data1 = json_decode(file_get_contents("data1.json"), true);
$data2 = json_decode(file_get_contents("data2.json"), true);
$dataTotal = json_decode(file_get_contents("datatotal.json"), true);
$sliteRule = json_decode(file_get_contents("sliteRule.json"), true);

$dataArray = array(
    'box1' => $data1['value'],
    'box2' => $data2['value'],
    'errorNum1' => $data1['errorNum'],
    'errorNum2' => $data2['errorNum'],
    'sethtml1' => $data1['sethtml'],
    'sethtml2' => $data2['sethtml'],
    'total' => $dataTotal['total'],
    'sliteRule' => $sliteRule['value']
);
echo json_encode($dataArray);