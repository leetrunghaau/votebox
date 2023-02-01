<?php
$id = $_GET['id'];
$value = $_GET['total'];
$status = 'thay đổi không thành công';

if($id == null || $value == null || !is_numeric($value)){
    $status = 'thay đổi không thành công';
}else{
    $dataArray = json_decode(file_get_contents("data.json"), true);
    if($id == 'thung1'){
        $dataArray['thung1']['total'] = (int)$value;
        $status = 'đã lưu thay đổi';
    }elseif($id == 'thung2'){
        $dataArray['thung2']['total'] = (int)$value;
        $status = 'đã lưu thay đổi';
    }
    elseif($id == 'total'){
        $dataArray['total']['total'] = (int)$value;
        $status = 'đã lưu thay đổi';
    }
    file_put_contents("data.json",json_encode($dataArray));
}
echo $status;