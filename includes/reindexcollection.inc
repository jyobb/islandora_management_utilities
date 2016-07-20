<?php
/*
 * @params Collection $pid, Datastream type (MODS, DC)
 *
 * Test the PID to ensure it is a collection and query for all 
 * child objects.
 *
 * Send result to datastream specific analyzer function
 *
 */
function islandora_reindex_collection($params){

  $pid = $params['parentPID'];
  $getchildren = $params['reindexcollection'];
  $user = $params['user'];
  $pass = $params['pass'];

  $pid_list = array();

  collect_pids($pid, $getchildren, $pid_list);

  reindex_list($pid_list, $user, $pass);

}


/*
<input type="hidden" value="updateIndex" name="operation">
<input type="hidden" value="fromPid" name="action">
<input type="text" value="" size="30" name="value">
<input type="submit" value="updateIndex fromPid">


input type="hidden" value="updateIndex" name="operation">
<input type="hidden" value="optimize" name="action">
<input type="submit" value="updateIndex optimize">

   $url = $base_url . ":8080/fedoragsearch/rest?operation/updateIndex&action=optimize;
*/

function reindex_list($pid_list, $user, $pass) {

$status = array();
global $base_url;

$handle = fopen("/var/www/html/drupal/sites/all/modules/islandora_management_utilities/data/reindex_results.txt", "w");
$date = date("Y-m-d H:i:s");
fwrite($handle, $date . "\n");
$output = array();
foreach($pid_list as $p){
   $url = $base_url . ":8080/fedoragsearch/rest?operation/updateIndex&action=fromPid&value=" . $p;

   $ch = curl_init();
   curl_setopt($ch, CURLOPT_URL, $url);
   curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
   curl_setopt($ch, CURLOPT_USERPWD, "$user:$pass");
   curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
   $output = curl_exec($ch);
   $info = curl_getinfo($ch);
   fwrite($handle, "PID= ". $p . " http_code " . $info['http_code'] . "\n");
   curl_close($ch);
}

   $optimize_url = $base_url . ":8080/fedoragsearch/rest?operation=updateIndex&action=optimize";
   $ch = curl_init();
   curl_setopt($ch, CURLOPT_URL, $optimize_url);
   curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
   curl_setopt($ch, CURLOPT_USERPWD, "$user:$pass");
   curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
   $output = curl_exec($ch);
   $info = curl_getinfo($ch);
   fwrite($handle, "Optimize http_code " . $info['http_code'] . "\n");
   curl_close($ch);

fclose($handle);



}


function collect_pids($pid, $getchildren, &$pid_list){


  $collections = array('islandora:collectionCModel', 'islandora:bookCModel');

  $query = <<<EOQ
  SELECT ?pid FROM <#ri>
WHERE {
    {
  ?pid <fedora-rels-ext:isMemberOf> <info:fedora/$pid>
  }
  UNION
  {
  ?pid <fedora-rels-ext:isMemberOfCollection> <info:fedora/$pid>
  }
}
EOQ;
  $connection = islandora_get_tuque_connection();

  $sparql_count = $connection->repository->ri->countQuery($query, 'sparql');
  $results = $connection->repository->ri->sparqlQuery($query); 

foreach ($results as $result) {
  $fedoraObject = islandora_object_load($result['pid']['value']);

  $relationships = $fedoraObject->relationships->get('info:fedora/fedora-system:def/model#', 'hasModel');

  //Now check to see if this is a collection
  if(in_array($relationships[0]['object']['value'], $collections)){
    if($getchildren == '1') {     						    
      collect_pids($fedoraObject->id, TRUE, $pid_list);
    } //we can caputure the collection here
  } else {
    $pid_list[] = $fedoraObject->id;
  }

}

}






