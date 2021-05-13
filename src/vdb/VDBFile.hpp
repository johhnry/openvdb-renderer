#ifndef OPENVDB_RENDERER_SRC_VDB_FILE_HPP_
#define OPENVDB_RENDERER_SRC_VDB_FILE_HPP_

#include <openvdb/Grid.h>
#include <openvdb/openvdb.h>
#include <string>
#include <vector>

class VDBFile
{
public:
  VDBFile(std::string filename);
  virtual ~VDBFile() noexcept;

  VDBFile(const VDBFile &other) = delete;
  VDBFile(VDBFile &&other) noexcept = delete;
  VDBFile &operator=(const VDBFile &other) = delete;
  VDBFile &operator=(VDBFile &&other) noexcept = delete;

  std::vector<std::string> &getGridNames();
  void displayMetaData(int gridIndex);

  std::string filename;

private:
  openvdb::io::File *file;
  std::vector<std::string> gridNames;
  std::vector<openvdb::GridBase::Ptr> grids;
};

#endif /* OPENVDB_RENDERER_SRC_VDB_FILE_HPP_ */
