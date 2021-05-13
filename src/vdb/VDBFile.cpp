#include <imgui/imgui.h>
#include <openvdb/openvdb.h>

#include "VDBFile.hpp"
#include "log/Log.hpp"
#include <string>
#include <vector>
#include <iostream>

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

    openvdb::FloatGrid::Ptr grid =
        openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);

    using GridType = openvdb::FloatGrid;
    // Iterate over all active values but don't allow them to be changed.
    for (GridType::ValueOnCIter iter = grid->cbeginValueOn(); iter.test();
         ++iter) {
      // openvdb::Vec3f value = (openvdb::Vec3f) iter.getValue();

      // Print the coordinates of all voxels whose vector value has
      // a length greater than 10, and print the bounding box coordinates
      // of all tiles whose vector value length is greater than 10.
      if (iter.isVoxelValue()) {
        std::cout << iter.getCoord() << std::endl;
      } else {
        openvdb::CoordBBox bbox;
        iter.getBoundingBox(bbox);
        std::cout << bbox << std::endl;
      }
    }

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

std::vector<std::string> &VDBFile::getGridNames()
{
  return gridNames;
}
