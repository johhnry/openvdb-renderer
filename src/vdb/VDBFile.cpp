#include <string>
#include <vector>

#include "GL/glew.h"
#include <imgui/imgui.h>
#include <openvdb/math/Coord.h>
#include <openvdb/openvdb.h>

#include "VDBFile.hpp"
#include "geometry/CubeGeometry.hpp"
#include "log/Log.hpp"

std::string getGridType(openvdb::GridBase::Ptr grid)
{
  if (grid->isType<openvdb::BoolGrid>())
    return "BoolGrid";
  else if (grid->isType<openvdb::FloatGrid>())
    return "FloatGrid";
  else if (grid->isType<openvdb::DoubleGrid>())
    return "DoubleGrid";
  else if (grid->isType<openvdb::Int32Grid>())
    return "Int32Grid";
  else if (grid->isType<openvdb::Int64Grid>())
    return "Int64Grid";
  else if (grid->isType<openvdb::Vec3IGrid>())
    return "Vec3IGrid";
  else if (grid->isType<openvdb::Vec3SGrid>())
    return "Vec3SGrid";
  else if (grid->isType<openvdb::Vec3DGrid>())
    return "Vec3DGrid";
  else if (grid->isType<openvdb::StringGrid>())
    return "StringGrid";

  return "Type not found";
}

VDBFile::VDBFile(std::string filename)
  : filename(filename)
{
  Log::info("Creating .vdb file " + filename);

  file = new openvdb::io::File(filename);
  file->open();
  Log::success("Opened VDB file " + filename);

  // Iterate over grid names
  for (openvdb::io::File::NameIterator nameIter = file->beginName();
       nameIter != file->endName(); ++nameIter) {

    // Get grid name and read it from file
    std::string gridName = nameIter.gridName();
    openvdb::GridBase::Ptr baseGrid = file->readGrid(gridName);

    gridNames.push_back(gridName + " (" + getGridType(baseGrid) + ")");
    grids.push_back(baseGrid);

    Log::message(nameIter.gridName());
  }
}

VDBFile::~VDBFile() noexcept
{
  file->close();
}

void VDBFile::displayMetaData(int gridIndex)
{
  if (ImGui::BeginTable("MetaData", 2)) {
    ImGui::TableSetupColumn("Key");
    ImGui::TableSetupColumn("Value");
    ImGui::TableHeadersRow();


    openvdb::GridBase::Ptr grid = grids.at(gridIndex);

    for (openvdb::MetaMap::MetaIterator iter = grid->beginMeta();
         iter != grid->endMeta(); ++iter) {
      const std::string &name = iter->first;
      openvdb::Metadata::Ptr value = iter->second;

      ImGui::TableNextColumn();
      ImGui::Text("%s", name.c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%s", value->str().c_str());
    }

    ImGui::EndTable();
  }
}

void VDBFile::constructPointCloud(int gridIndex) {
  // Remove previous cubes
  cubes.clear();

  using GridType = openvdb::FloatGrid;
  GridType::Ptr grid =
      openvdb::gridPtrCast<openvdb::FloatGrid>(grids.at(gridIndex));

  int nbVoxels = 0;
  int nbPut = 0;
  for (GridType::ValueOnCIter iter = grid->cbeginValueOn(); iter.test();
       ++iter) {
    if (iter.isVoxelValue() && nbVoxels % 100 == 0) {
      openvdb::math::Coord pt = iter.getCoord();

      IGeometry *cube =
          new CubeGeometry(pt.x() / 100.0, pt.y() / 100.0, pt.z() / 100.0, 1.0);
      cubes.emplace_back(std::unique_ptr<IGeometry>(cube));

      nbPut++;
    }

    nbVoxels++;
  }

  Log::success("Created " + std::to_string(nbPut) + " cubes!");
}

void VDBFile::draw(Program &displayProgram, float scale) {
  // Draw cubes
  for (size_t i = 0; i < cubes.size(); i++) {
    cubes.at(i)->setScale(scale);
    cubes.at(i)->draw(displayProgram);
  }
}

std::vector<std::string> &VDBFile::getGridNames()
{
  return gridNames;
}
