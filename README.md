# ProjectX

## Build Status

CI: ![travis](https://travis-ci.org/MoKob/ProjectX.svg?branch=master)

Coverage: [![codecov](https://codecov.io/gh/MoKob/ProjectX/branch/master/graph/badge.svg)](https://codecov.io/gh/MoKob/ProjectX)

## Building

Dependencies:
```
apt-get install libboost-all-dev
```

## Building a Graph from OSM

Dependencies:
```
sudo apt-get install build-essential libboost-python-dev \
                     libexpat1-dev zlib1g-dev libbz2-dev
pip3 install osmium
```

Run
```
python3 scripts/python/import-osm.py osm.pbf result.xgraph
```
