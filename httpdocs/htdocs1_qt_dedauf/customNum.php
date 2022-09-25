<?php
$id = $_GET['id'];
$value = $_GET['value'];
$status = 'false';

if($id == null || $value == null){
    $status = 'false';
}else{
    $dataArray = json_decode(file_get_contents("data.json"), true);
    if($id == 'thung1'){
       
        if($value == 'add'){
            $dataArray['thung1']['errorNum'] = $dataArray['thung1']['errorNum'] +1;
            $status = $dataArray['thung1']['errorNum'];
        }else if($value == 'sub'){
            $dataArray['thung1']['errorNum'] = $dataArray['thung1']['errorNum'] - 1;
            $status = $dataArray['thung1']['errorNum'];
        }else if ($value == 'zero'){
            $dataArray['thung1']['errorNum'] = 0;
            $status = $dataArray['thung1']['errorNum'];
        }
        
    }elseif($id == 'thung2'){
        if($value == 'add'){
            $dataArray['thung2']['errorNum'] = $dataArray['thung2']['errorNum'] +1;
            $status = $dataArray['thung2']['errorNum'];
        }else if($value == 'sub'){
            $dataArray['thung2']['errorNum'] = $dataArray['thung2']['errorNum'] - 1;
            $status = $dataArray['thung2']['errorNum'];
        }else if ($value == 'zero'){
            $dataArray['thung2']['errorNum'] = 0;
            $status = $dataArray['thung2']['errorNum'];
        }
        
    }
    file_put_contents("data.json",json_encode($dataArray));
}
echo $status;
