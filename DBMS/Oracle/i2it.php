<!DOCTYPE html>
<html>
<head>
    <title>Image Upload</title>
</head>
<body style="background-color:LightSeaGreen; font-family: Arial, sans-serif; color: white; text-align: center; padding: 50px;">

<h2>Upload an Image</h2>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $target_dir = "i2it/";
    // Make sure the directory exists or create it
    if (!is_dir($target_dir)) {
        mkdir($target_dir, 0755, true);
    }

    $target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
    $uploadOk = 1;
    $imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));

    // Check if image file is an actual image or fake image
    $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
    if ($check !== false) {
        echo "File is an image - " . htmlspecialchars($check["mime"]) . ".<br>";
        $uploadOk = 1;
    } else {
        echo "File is not an image.<br>";
        $uploadOk = 0;
    }

    // Check if file already exists
    if (file_exists($target_file)) {
        echo "Sorry, file already exists.<br>";
        $uploadOk = 0;
    }

    // Check file size (limit 500 KB)
    if ($_FILES["fileToUpload"]["size"] > 500000) {
        echo "Sorry, your file is too large. Max 500 KB allowed.<br>";
        $uploadOk = 0;
    }

    // Allow certain file formats
    $allowedFormats = ["jpg", "jpeg", "png", "gif"];
    if (!in_array($imageFileType, $allowedFormats)) {
        echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.<br>";
        $uploadOk = 0;
    }

    // Check if everything is ok
    if ($uploadOk == 0) {
        echo "Sorry, your file was not uploaded.<br>";
    } else {
        if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
            echo "The file ". htmlspecialchars(basename($_FILES["fileToUpload"]["name"])) . " has been uploaded.<br>";
        } else {
            echo "Sorry, there was an error uploading your file.<br>";
        }
    }
}
?>

<!-- File Upload Form -->
<form action="" method="post" enctype="multipart/form-data" style="margin-top: 30px;">
    <input type="file" name="fileToUpload" id="fileToUpload" required>
    <br><br>
    <input type="submit" value="Upload Image" name="submit" style="padding: 10px 20px; font-size: 16px; cursor: pointer;">
</form>

<!-- Link to check uploaded files -->
<br><br>
<a href="http://localhost/i2it.php" style="color: white; text-decoration: underline;">Check Your File Is Uploaded OR Not</a>

</body>
</html>
