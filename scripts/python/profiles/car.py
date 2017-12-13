# A car profile that decides usage / non usage of OSM tags

#from sets import Set

class OSMCar:
    def __init__(self):
        self.highway_speeds = {'motorway': 90,
                               'motorway_link': 40,
                               'trunk': 80,
                               'trunk_link': 35,
                               'primary': 50,
                               'primary_link': 35,
                               'secondary': 45,
                               'secondary_link': 30,
                               'tertiary': 40,
                               'tertiary_link': 30,
                               'unclassified': 40,
                               'residential': 30,
                               'living_street': 10,
                               'service': 5}

    # check if a way is valid for the profile
    def valid(self,osm_way):
        return 'highway' in osm_way.tags and osm_way.tags['highway'] in self.highway_speeds

    # translate a way into its travelling speed
    def get_speed(self,osm_way):
        if osm_way.tags['highway'] not in self.highway_speeds:
            raise InvalidArgument

        return self.highway_speeds[osm_way.tags['highway']]
