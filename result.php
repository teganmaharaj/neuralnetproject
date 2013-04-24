<?

/*
Where the magic happens!
This code takes a json object from POST data and draws it to an image.

Then it scales down the image to a size that is managable by the neural net, and converts it to a binary string by iterating over each of the pixels and returning either a 1 for a painted region or 0 for empty.
When the string is prepared it executes the Neural net code with the required arguments.

*/

//This function was grabbed from Thomas Bradley's  signature-to-image library, it converts a properly formatted javascript object to an image.
function drawThickLine ($img, $startX, $startY, $endX, $endY, $colour, $thickness) {
  $angle = (atan2(($startY - $endY), ($endX - $startX)));

  $dist_x = $thickness * (sin($angle));
  $dist_y = $thickness * (cos($angle));

  $p1x = ceil(($startX + $dist_x));
  $p1y = ceil(($startY + $dist_y));
  $p2x = ceil(($endX + $dist_x));
  $p2y = ceil(($endY + $dist_y));
  $p3x = ceil(($endX - $dist_x));
  $p3y = ceil(($endY - $dist_y));
  $p4x = ceil(($startX - $dist_x));
  $p4y = ceil(($startY - $dist_y));

  $array = array(0=>$p1x, $p1y, $p2x, $p2y, $p3x, $p3y, $p4x, $p4y);
  imagefilledpolygon($img, $array, (count($array)/2), $colour);
}

//grab the json from the form submit
$json = $_POST['output'];


//set the size of our initial image. This must match the size of the canvas element.
$width = 100;
$height = 150;
$penWidth = 10;
$penColour = array(0x00, 0x00, 0x00);

/*
These varaibles influences the scaling for the second image, they were found to be a good balance of detail to processability within the net.
Passing a larger image with more detail greatly increases the required size of the neural net, and therefore increasing required processing and training time.
*/

$percent = 0.2;
$newwidth = $width * $percent;
$newheight = $height * $percent;

//make us a blank image with PHP's built-in image functions
$img = imagecreatetruecolor($width, $height);
imagesavealpha($img, true);
$bg = imagecolorallocatealpha($img, 0, 0, 0, 127);
$pen = imagecolorallocate($img, $penColour[0], $penColour[1], $penColour[2]);
imagefill($img, 0, 0, $bg);

//so long as we got the right input from the form,
if (is_string($json))
    $json = json_decode(stripslashes($json));

//paint each line to our first image
foreach ($json as $v)
    drawThickLine($img, $v->lx, $v->ly, $v->mx, $v->my, $pen, $penWidth * (.5));

//make a second, blank image for our scaled down output.
$img2 = imagecreatetruecolor($newwidth, $newheight);
imagealphablending($img2, false);
imagesavealpha($img2, true);

//imagecopyresampled resizes it down to our new specifications (set with $percent)
imagecopyresampled($img2, $img, 0, 0, 0, 0, $newwidth, $newheight, $width, $height);

//iterate over each pixel in the scaled down image, and return a formatted string.
function printImg() {
  global $newwidth, $newheight, $img2;
    for ($y2=0; $y2 < $newheight; $y2++) {
        for ($x2=0; $x2 < $newwidth; $x2++) {
                if (imagecolorat($img2, $x2, $y2) == 0){
                    $string .= "1";
                } else {
                    $string .= "0";
                }
        }
    }
    return $string;
}

//This would draw the resized image to the page, useful for testing only.
//header('Content-Type: image/png');
//imagepng($img2);


//result.php is used by both train.php and index.php to submit the data to the server, this if statement ensures that the request is actually coming from the same server's train.php for security purposes.
//then the result string is set to the proper command that will execute the neural net.
if (isset($_POST['number']) && $_POST['number'] < 10 && $_POST['number'] >= 0 && "http://".$_SERVER["SERVER_NAME"]."/train.php" == $_SERVER["HTTP_REFERER"]) {
    $result = "./cpp/train ./cpp/final.net ".printImg()." ".$_POST['number']; //submit a train request, with the number to be trained
} else {
    $result = "./cpp/frozen ./cpp/final.net ".printImg()." -1"; //submit a query, with a garbage argument.
}

//the following line prints the command to the page, useful when debugging the C++, as you can directly run/modify the commands that the server is sending.
//print $result."</br>";

//executes the output, and saves the return value
$output = exec($result,$op,$ret_val);

//prints the output to the page, so we can evaluate the last line of the query in testing.
//print $output."</br>";

//if the command returned unsuccessfully, print an error to the page. - If you end up heavily modifying this project you may want to make and point to a proper error page.
if ($ret_val != 0) {
  print "ERROR!</br>Returned: ".$ret_val."</br>Result: ".$result."</br>Var Dump: ";
  var_dump(parse_str($output));
}

//couple other details about the executed command, can be used in further debugging.
//print $op."</br>";
//print "</br>".$output."</br>";

//we assume the command executed successfully, and returned a properly delimited string for use in the results
parse_str($output);

//as the neural net returns weights as decimals (0.48 is 48%) and bootstrap's progress bars only handles integers >= 0 and <= 100, this function formats them properly.
function clean($string) {
    if ($string == 1) {
        return "100";
    } else {
        $string = $string*100;
        return substr($string, 0, 2);
    }    
}

//do some garbage collection
imagedestroy($img);
imagedestroy($img2);
?>
<!DOCTYPE html>
<head>
  <meta charset="utf-8">
  <title>S.E.A.N.N. - Results</title>
  <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
  <link href="css/seann.css" rel="stylesheet" media="screen">
</head>

<body>
    <div class="container-fluid">
        <div class="well">
            <center>
              <a class="btn btn-success" href="./"><i class="icon-home icon-white"></i> Home</a>
              <!-- It would be a good idea to put authentication on the training page, to avoid malicious users from modifying or clearing your brainfile. You can comment out the following button to make it less accessable to users. -->
              <a class="btn btn-warning" href="./train.php"><i class="icon-pencil icon-white"></i> Train</a>
            </center>
          <dl>
            <dt>0. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var0); ?>%;"></div></div></dt>
            <dt>1. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var1); ?>%;"></div></div></dt>
            <dt>2. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var2); ?>%;"></div></div></dt>
            <dt>3. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var3); ?>%;"></div></div></dt>
            <dt>4. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var4); ?>%;"></div></div></dt>
            <dt>5. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var5); ?>%;"></div></div></dt>
            <dt>6. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var6); ?>%;"></div></div></dt>
            <dt>7. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var7); ?>%;"></div></div></dt>
            <dt>8. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var8); ?>%;"></div></div></dt>
            <dt>9. </dt><dd><div class="progress"><div class="bar" style="width: <? echo clean($var9); ?>%;"></div></div></dt>
          </dl>
        </div>
    </div>

</body>