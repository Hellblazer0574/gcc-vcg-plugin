/* Dump or view gcc tree structure hierarchy.

   Copyright (C) 2010, 2011 Mingjie Xing, mingjie.xing@gmail.com.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */ 

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "gcc-plugin.h"
#include "plugin.h"
#include "plugin-version.h"

#include "vcg-plugin.h"

/* Create the tree hierarchy graph.  */

static gdl_graph *
create_tree_hierarchy_graph (void)
{
  gdl_graph *graph;
  gdl_node *node;
  gdl_edge *edge;

  graph = gdl_new_graph ("tree hierarchy");
  gdl_set_graph_orientation (graph, "left_to_right");
  gdl_set_graph_node_borderwidth (graph, 1);
  gdl_set_graph_edge_thickness (graph, 1);

  #define NEW_NODE(name) \
  node = gdl_new_node (name); \
  gdl_set_node_label (node, name); \
  gdl_add_node (graph, node);

  NEW_NODE ("tree_base")
  NEW_NODE ("tree_common")
  NEW_NODE ("tree_int_cst")
  NEW_NODE ("tree_real_cst")
  NEW_NODE ("tree_fixed_cst")
  NEW_NODE ("tree_vector")
  NEW_NODE ("tree_string")
  NEW_NODE ("tree_complex")
  NEW_NODE ("tree_identifier")
  NEW_NODE ("tree_decl_minimal")
  NEW_NODE ("tree_decl_common")
  NEW_NODE ("tree_decl_with_rtl")
  NEW_NODE ("tree_decl_non_common")
  NEW_NODE ("tree_parm_decl")
  NEW_NODE ("tree_decl_with_vis")
  NEW_NODE ("tree_var_decl")
  NEW_NODE ("tree_field_decl")
  NEW_NODE ("tree_label_decl")
  NEW_NODE ("tree_result_decl")
  NEW_NODE ("tree_const_decl")
  NEW_NODE ("tree_type_decl")
  NEW_NODE ("tree_function_decl")
  NEW_NODE ("tree_translation_unit_decl")
  NEW_NODE ("tree_type")
  NEW_NODE ("tree_list")
  NEW_NODE ("tree_vec")
  NEW_NODE ("tree_exp")
  NEW_NODE ("tree_ssa_name")
  NEW_NODE ("tree_block")
  NEW_NODE ("tree_binfo")
  NEW_NODE ("tree_statement_list")
  NEW_NODE ("tree_constructor")
  NEW_NODE ("tree_omp_clause")
  NEW_NODE ("tree_optimization_option")
  NEW_NODE ("tree_target_option")

  #define NEW_EDGE(src, dest) \
  edge = gdl_new_edge (src, dest); \
  gdl_add_edge (graph, edge);

  NEW_EDGE ("tree_base", "tree_common")
  NEW_EDGE ("tree_common", "tree_int_cst")
  NEW_EDGE ("tree_common", "tree_real_cst")
  NEW_EDGE ("tree_common", "tree_fixed_cst")
  NEW_EDGE ("tree_common", "tree_string")
  NEW_EDGE ("tree_common", "tree_complex")
  NEW_EDGE ("tree_common", "tree_vector")
  NEW_EDGE ("tree_common", "tree_identifier")
  NEW_EDGE ("tree_common", "tree_list")
  NEW_EDGE ("tree_common", "tree_vec")
  NEW_EDGE ("tree_common", "tree_constructor")
  NEW_EDGE ("tree_common", "tree_exp")
  NEW_EDGE ("tree_common", "tree_ssa_name")
  NEW_EDGE ("tree_common", "tree_omp_clause")
  NEW_EDGE ("tree_common", "tree_block")
  NEW_EDGE ("tree_common", "tree_type")
  NEW_EDGE ("tree_common", "tree_binfo")
  NEW_EDGE ("tree_common", "tree_decl_minimal")
  NEW_EDGE ("tree_decl_minimal", "tree_decl_common")
  NEW_EDGE ("tree_decl_common", "tree_decl_with_rtl")
  NEW_EDGE ("tree_decl_common", "tree_field_decl")
  NEW_EDGE ("tree_decl_with_rtl", "tree_label_decl")
  NEW_EDGE ("tree_decl_with_rtl", "tree_result_decl")
  NEW_EDGE ("tree_decl_with_rtl", "tree_const_decl")
  NEW_EDGE ("tree_decl_with_rtl", "tree_parm_decl")
  NEW_EDGE ("tree_decl_with_rtl", "tree_decl_with_vis")
  NEW_EDGE ("tree_decl_with_vis", "tree_var_decl")
  NEW_EDGE ("tree_decl_with_vis", "tree_decl_non_common")
  NEW_EDGE ("tree_decl_non_common", "tree_function_decl")
  NEW_EDGE ("tree_decl_common", "tree_translation_unit_decl")
  NEW_EDGE ("tree_decl_non_common", "tree_type_decl")
  NEW_EDGE ("tree_common", "tree_statement_list")
  NEW_EDGE ("tree_common", "tree_optimization_option")
  NEW_EDGE ("tree_common", "tree_target_option")

  return graph;
}

static void
dump_tree_hierarchy_to_file (char *fname)
{
  FILE *fp;
  gdl_graph *graph;

  if ((fp = fopen (fname, "w")) == NULL)
    {
      vcg_plugin_common.error ("failed to open file %s.", fname);
      return;
    }

  graph = create_tree_hierarchy_graph ();
  gdl_dump_graph (fp, graph);
  gdl_free_graph (graph);

  fclose (fp);
}

/* Public function to dump the gcc tree structure hierarchy.  */

void
vcg_plugin_dump_tree_hierarchy (void)
{
  char *fname = "dump-tree-hierarchy.vcg";

  /* Get the temp file name.  */
  dump_tree_hierarchy_to_file (fname);
}

/* Public function to view the gcc tree structure hierarchy.  */

void
vcg_plugin_view_tree_hierarchy (void)
{
  char *fname;

  /* Get the temp file name.  */
  fname = vcg_plugin_common.temp_file_name;
  dump_tree_hierarchy_to_file (fname);
  vcg_plugin_common.show (fname);
}
