<?php
header('Content-type: text/plain');
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

$json = $_POST['output'];
$width = 100;
$height = 150;
$penWidth = 10;
$penColour = array(0x00, 0x00, 0x00);

$percent = 0.2;
$newwidth = $width * $percent;
$newheight = $height * $percent;

$img = imagecreatetruecolor($width, $height);
imagesavealpha($img, true);
$bg = imagecolorallocatealpha($img, 0, 0, 0, 127);
$pen = imagecolorallocate($img, $penColour[0], $penColour[1], $penColour[2]);
imagefill($img, 0, 0, $bg);

if (is_string($json))
	$json = json_decode(stripslashes($json));

foreach ($json as $v)
	drawThickLine($img, $v->lx, $v->ly, $v->mx, $v->my, $pen, $penWidth * (.5));

$img2 = imagecreatetruecolor($newwidth, $newheight);
imagealphablending($img2, false);
imagesavealpha($img2, true);
imagecopyresampled($img2, $img, 0, 0, 0, 0, $newwidth, $newheight, $width, $height);

/*
for ($y=0; $y < $height; $y++) {
	for ($x=0; $x < $width; $x++) {
			if (imagecolorat($img, $x, $y) == 0){
				print '1';
			} else {
				print '0';
			}
	}
	print "\n";
}
*/
print "./frozen brainfile ";
for ($y2=0; $y2 < $newheight; $y2++) {
	for ($x2=0; $x2 < $newwidth; $x2++) {
			if (imagecolorat($img2, $x2, $y2) == 0){
				print '1';
			} else {
				print '0';
			}
	}
}
print " -1";

//exec('neuralnet'+$_POST['value']+$string);

//$date = new DateTime();
//$filename = $date->format('U = Y-m-d-H-i-s')+'x'+$_POST['value'];


//header('Content-Type: image/png');
//imagepng($img2);

// Save to file
//imagepng($img, $filename+'.png');

imagedestroy($img);
imagedestroy($img2);
?>
