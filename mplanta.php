<!DOCTYPE html>
<html lang="zxx">
<?php error_reporting(0);
 include_once'./cabezera.php';  
   include_once'./conexion.php';
   $conn = $mysqli;
$cod=$_GET['cod'];
   ?>

<body>
   
    
        <div class="container-fluid py-md-5 inner-sec-w3ls">
          
                    <div class="form">
                        <h3 class="text-capitalize mb-4 text-center">MODIFICANDO PLANTA</h3>
                        <form action="control/cplanta.php" method="post">
                            <?php $query = "SELECT * FROM hidroponia.plantas p join tplanta tp on p.idtplanta=tp.idtplanta  where p.idplantas=$cod;";

    $planta = $conn->query($query); 
 while ($row = $planta->fetch_array()) {
    ?>
                             <h5>CODIGO DE PLANTA<font color="red">*</font>:</h5>
                             <div class="input-group mt-3">
                                <input type="text" name=" tcod" class="form-control" placeholder="Ingrese Codigo" required="" readonly="" value=" <?php echo $row[0]?>">
                               
                            </div>

                            <h5>NOMBRE DE PLANTA<font color="red">*</font>:</h5>
                            <div class="input-group mt-3">
                                <input type="text" name=" tnom" class="form-control" placeholder="Ingrese Nombre de la Planta" required="" value=" <?php echo $row[1]?>">
                                
                            </div>
                         <div class="input-group mt-3">
<?php $query = "SELECT * FROM hidroponia.tplanta where concat(idtplanta,descr) like '%%';";

    $tplantas = $conn->query($query);

         ?>
                               <select class="form-control" name="tplan" >
                                <option value="<?php echo $row[3] ?>"><?php echo $row[4] ?></option>
                                <?php   while ($fila = $tplantas->fetch_array()) {?>
                                <option value="<?php echo $fila[0] ?>"><?php echo $fila[1] ?></option>
                            <?php } ?>
                              </select>

                            </div>
                            <div class="input-group1 mt-3">
                                <button class="submit btn form-control" value="M" name="baccion">MODIFICAR</button>
                                <a href="planta.php"><button type="button" class="btn btn form-control">ATRAS</button></a> 
                            </div>
                        <?php } ?>
                        </form>
                    </div>

            

        </div>
   
 
</body>

</html>