# Python importer for OSM files using

import osmium
import sys
import xpython
from itertools import islice
from profiles.car import OSMCar

class ImportHandler(osmium.SimpleHandler):
    def __init__(self, profile, builder):
        super(ImportHandler, self).__init__()
        self.profile = profile
        self.builder = builder

    def way(self, osm_way):
        # check if the way has a highway tag
        if 'highway' in osm_way.tags:
            if self.profile.valid(osm_way):
                self.add_way(osm_way)

    # add a way (checked) to the builder 
    def add_way(self,osm_way):
        for cur, nex in zip(osm_way.nodes,islice(osm_way.nodes,1,None)):
            source = int(str(cur))
            target = int(str(nex))
            # segment length in meters
            length = get_distance(osm_way,source,target);
            # time in seconds
            time = length / self.profile.get_speed(osm_way.tags['highway']) / 3.6
            # shortest time routing in deci-sceonds, all values stored with deci-accuracy
            self.builder.add_edge(source, target, 10 * time, 10 * time, 10 * length, osm_way.tags['highway'])
        
# running the handler
if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Usage: python import-osm.py <osmfile> <output>')
        sys.exit(0)
   
    builder = xpython.importer.GraphBuilder()
    importer = ImportHandler(OSMCar(),builder)
    importer.apply_file(sys.argv[1])
    builder.build_graph_and_store(sys.argv[2]) 
