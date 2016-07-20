<?php

/**
 * @file
 * Drush hooks.
 */

/**
 * Implements hook_drush_command().
 */

function islandora_management_utilities_drush_command() {
  $items = array();

  $items['islandora_checkstreams'] = array(
    'aliases' => array('icd'),
    'description' => 'Check datastream exists for all object in a collection.',
    'drupal dependencies' => array('islandora_management_utilities'),
    'examples' => array(
     'drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_checkstreams --parentpid="apid:111" --datastream="MODS" --outfile="outfilename.txt"',
    ),
    'options' => array(
      'parentpid' => array(
        'description' => 'collections object pid',
        'required' => TRUE,
      ),
      'datastream' => array(
        'description' => 'Target datastream to look for',
        'required' => TRUE,
      ),
      'outfile' => array(
        'description' => 'File name to save output',
        'required' => TRUE,
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  $items['islandora_checkmimes'] = array(
    'aliases' => array('icm'),
    'description' => 'Check the mimetypes of a collection are correct.',
    'drupal dependencies' => array('islandora_management_utilities'),
    'examples' => array(
     'drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_checkmimes --parentpid="apid:111" --datastream="MODS" --outfile="outfilename.txt"',
    ),
    'options' => array(
      'parentpid' => array(
        'description' => 'collections object pid',
        'required' => TRUE,
      ),
      'datastream' => array(
        'description' => 'Target datastream to look for',
        'required' => TRUE,
      ),
      'outfile' => array(
        'description' => 'File name to save output',
        'required' => TRUE,
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  $items['islandora_fixmimes'] = array(
    'aliases' => array('ifm'),
    'description' => 'Change object mimetype.',
    'drupal dependencies' => array('islandora_management_utilities'),
    'examples' => array(
     'drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_fixmimes --parentpid="apid:111" --datastream="MODS" --currmime="image/tif" --newmime="image/tiff" --outfile="outfilename.txt"',
    ),
    'options' => array(
      'parentpid' => array(
        'description' => 'collections object pid',
        'required' => TRUE,
      ),
      'datastream' => array(
        'description' => 'Target datastream to look for',
        'required' => TRUE,
      ),
      'outfile' => array(
        'description' => 'File name to save output',
        'required' => TRUE,
      ),
      'currmime' => array(
        'description' => 'Current Mimetype',
        'required' => TRUE,
      ),
      'newmime' => array(
        'description' => 'New Mimetype',
        'required' => TRUE,
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

  $items['islandora_reindex_collection'] = array(
    'aliases' => array('irc'),
    'description' => 'Reindex a collection and its children.',
    'drupal dependencies' => array('islandora_management_utilities'),
    'examples' => array(
     'drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_reindex_collection --parentpid="apid:111" --reindexchildren=TRUE --fedoraUser=username --fedoraPass=pass',
    ),
    'options' => array(
      'parentpid' => array(
        'description' => 'Collection object pid',
        'required' => TRUE,
      ),
      'reindexchildren' => array(
        'description' => 'Reindex Child Collections',
        'required' => TRUE,
      ),
      'fedoraUser' => array(
        'description' => 'Fedoragsearch Username',
        'required' => TRUE,
      ),
      'fedoraPass' => array(
        'description' => 'Fedoragsearch Password',
        'required' => TRUE,
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

return $items;

}


function drush_islandora_management_utilities_islandora_reindex_collection(){
  /*
  $parentPID = drush_get_option('parentpid');
  $dataStream = drush_get_option('reindexchildren');
  $user = drush_get_option('fedoraUser');
  $pass = drush_get_option('fedoraPass');
  */
  $params = array('parentPID' => drush_get_option('parentpid'), 
                'reindexcollection' => drush_get_option('reindexchildren'),
                'user' => drush_get_option('fedoraUser'),
                'pass' => drush_get_option('fedoraPass'),
               );  



  $base = drupal_get_path('module', 'islandora_management_utilities');

  //$filepath = DRUPAL_ROOT . '/' . $base . '/data/' . $outFilename;

module_load_include('inc', 'islandora_management_utilities', 'includes/reindexcollection');

islandora_reindex_collection($parentPID, $reindexchildren);

}




function drush_islandora_management_utilities_islandora_checkmimes(){

  $parentPID = drush_get_option('parentpid');
  $dataStream = drush_get_option('datastream');
  $outFilename = drush_get_option('outfile');

  $base = drupal_get_path('module', 'islandora_management_utilities');

  $filepath = DRUPAL_ROOT . '/' . $base . '/data/' . $outFilename;


module_load_include('inc', 'islandora_management_utilities', 'includes/analyzer');

islandora_get_mime_types($parentPID, $dataStream, $filepath );

}

function drush_islandora_management_utilities_islandora_fixmimes(){

  $parentPID = drush_get_option('parentpid');
  $dataStream = drush_get_option('datastream');
  $outFilename = drush_get_option('outfile');
  $currmime = drush_get_option('currmime');
  $newmime = drush_get_option('newmime');

  $base = drupal_get_path('module', 'islandora_management_utilities');

  $filepath = DRUPAL_ROOT . '/' . $base . '/data/' . $outFilename;


module_load_include('inc', 'islandora_management_utilities', 'includes/analyzer');

islandora_fix_mime_types($parentPID, $dataStream, $filepath, $currmime, $newmime );

}






/**
 * Implements drush_COMMAND_validate() for islandora_checkstreams
 */
function drush_islandora_management_utilities_validate() {
  
  //Test file exists
  /*
  $base = drupal_get_path('module', 'islandora_checkstreams');
  $filepath = drush_get_option('outfile');
  if (!file_exists($base . '/data/' .$filepath)) {
    drush_set_error('FILE EXISTS');
  }

  //Add test for datastreams

*/
}



function drush_islandora_management_utilities_islandora_checkstreams(){

  $parentPID = drush_get_option('parentpid');
  $dataStream = drush_get_option('datastream');
  $outFilename = drush_get_option('outfile');

  $base = drupal_get_path('module', 'islandora_management_utilities');

  $filepath = DRUPAL_ROOT . '/' . $base . '/data/' . $outFilename;

module_load_include('inc', 'islandora_management_utilities', 'includes/analyzer');

islandora_get_missing_datastreams($parentPID, $dataStream, $filepath );

}
