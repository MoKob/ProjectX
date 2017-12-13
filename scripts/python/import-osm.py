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
        if self.profile.valid(osm_way):
            self.add_way(osm_way)

    # add a way (checked) to the builder 
    def add_way(self,osm_way):
        for cur, nex in zip(osm_way.nodes,islice(osm_way.nodes,1,None)):
            source = int(str(cur))
            target = int(str(nex))
            #distance in meters
            length = 1.0 # get_distance(osm_way,cur,nex)
            #time in seconds
            time = length / self.profile.get_speed(osm_way)
            #compute a good routing weight: TODO
            weight = time
            self.builder.add_edge(source, target, int(10*weight), int(10*time), int(10*length), osm_way.tags['highway'])
        
# running the handler
if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Usage: python import-osm.py <osmfile> <output>')
        sys.exit(0)
   
    builder = xpython.importer.WeightTimeDistanceGraph()
    importer = ImportHandler(OSMCar(),builder)
    importer.apply_file(sys.argv[1])
    builder.build_weighted_graph_and_store(sys.argv[2]) 
