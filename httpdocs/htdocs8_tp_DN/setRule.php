<?php

$status = 'thay đổi không thành công';

$dataArray = json_decode(file_get_contents("sliteRule.json"), true);
if($dataArray['value'] == 0){
    $dataArray['value'] = 1;
    $status = 'on';
}else{
    $dataArray['value'] = 0;
    $status = 'off';
}
file_put_contents("sliteRule.json", json_encode($dataArray));
echo $status;