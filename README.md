# islandora_mangement_utilities
Check integrity of islandora objects
Reindex a collection and its children

# Requirements
Drush

# Installation
Install as usual.

drush -v --user=admin --uri=http://islandorasev_dev.ca islandora_check_for_datastream --parentpid="apid:111" --datastream="MODS,DC" --outfile="filename"




