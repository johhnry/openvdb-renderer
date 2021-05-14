#ifndef OPENVDB_RENDERER_SRC_VDB_FILE_HPP_
#define OPENVDB_RENDERER_SRC_VDB_FILE_HPP_

#include <string>
#include <vector>

#include <openvdb/Grid.h>
#include <openvdb/openvdb.h>

#include "geometry/IGeometry.hpp"
#include "scene/Camera.hpp"

class VDBFile {
public:
  VDBFile(std::string filename);
  virtual ~VDBFile() noexcept;

  VDBFile(const VDBFile &other) = delete;
  VDBFile(VDBFile &&other) noexcept = delete;
  VDBFile &operator=(const VDBFile &other) = delete;
  VDBFile &operator=(VDBFile &&other) noexcept = delete;

  std::vector<std::string> &getGridNames();
  void displayMetaData(int gridIndex);
  void draw(Program &displayProgram, float scale);

  void constructPointCloud(int gridIndex);

  std::string filename;

private:
  openvdb::io::File *file;
  std::vector<std::string> gridNames;
  std::vector<openvdb::GridBase::Ptr> grids;

  std::vector<std::unique_ptr<IGeometry>> cubes;
};

#endif /* OPENVDB_RENDERER_SRC_VDB_FILE_HPP_ */
