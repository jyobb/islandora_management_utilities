# islandora_mangement_utilities
Check integrity of islandora objects
Reindex a collection and its children

# Requirements
Drush

# Installation
Install as usual.

#Drush Commands included

Find out what items in a collection have a specific datastream
drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_checkstreams --parentpid="apid:111" --datastream="MODS" --outfile="outfilename.txt"

Check to see the mimetypes of a datastream
drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_checkmimes --parentpid="apid:111" --datastream="MODS" --outfile="outfilename.txt"

Change the mimetypes of a datastream for items in a collection
drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_fixmimes --parentpid="apid:111" --datastream="MODS" --currmime="image/tif" --newmime="image/tiff" --outfile="outfilename.txt"

Reindex a collection with solr
drush -v --user=fedora_admin --uri=http://islandorasev_dev.ca islandora_reindex_collection --parentpid="apid:111" --reindexchildren=TRUE --fedoraUser=username --fedoraPass=pass






