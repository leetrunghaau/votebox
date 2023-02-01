<?php

$value = $_GET['total'];
$status = 'thay đổi không thành công';

if ($value == null || !is_numeric($value)) {
    $status = 'thay đổi không thành công';
} else {
    $dataArray = json_decode(file_get_contents("datat2.json"), true);
    $dataArray['total'] = (int)$value;
    $status = 'đã lưu thay đổi';

    file_put_contents("datat2.json", json_encode($dataArray));
}
echo $status;
