
<!DOCTYPE html>
<html lang="zxx">

<?php 
error_reporting(0);
 
 include_once'./cabezera.php'; 

$conf=$_GET['tconf'];
if ($conf) {
 echo "<script>alert('Operacion Realizada exitosamente');</script>";

} ?>

<body>
   <center>
        <section class="principal">

  <h1>Jardines Registrados</h1>

  <div class="formulario">
    <label for="caja_busqueda">Buscar</label>
    <input type="text" name="caja_busqueda" id="caja_busqueda"></input> <a href="rjardin.php"><button class="btn btn-danger">Agregar Jardin</button></a>

    <br><br>
    
  </div>

  <div id="datos"></div>

</section>

<script type="text/javascript" src="js/jquery.min.js"></script>
<script type="text/javascript" src="js/bjardin.js"></script>
</center>
</body>

</html>
