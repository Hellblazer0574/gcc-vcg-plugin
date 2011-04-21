/* Dump or view gcc gimple statement structure hierarchy.

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

static void
dump_gimple_hierarchy_to_file (char *fname)
{
  FILE *fp;
  gdl_graph *graph;
  gdl_node *node;
  gdl_edge *edge;

  if ((fp = fopen (fname, "w")) == NULL)
    {
      vcg_plugin_common.error ("failed to open file %s.", fname);
      return;
    }

  graph = vcg_plugin_common.top_graph;
  gdl_set_graph_orientation (graph, "left_to_right");

  #define NEW_NODE(name) \
  node = gdl_new_node (name); \
  gdl_set_node_label (node, name); \
  gdl_add_node (graph, node);

  NEW_NODE ("gimple_statement_base")
  NEW_NODE ("gimple_statement_with_ops_base")
  NEW_NODE ("gimple_statement_with_ops")
  NEW_NODE ("gimple_statement_with_memory_ops_base")
  NEW_NODE ("gimple_statement_with_memory_ops")
  NEW_NODE ("gimple_statement_call")
  NEW_NODE ("gimple_statement_omp")
  NEW_NODE ("gimple_statement_bind")
  NEW_NODE ("gimple_statement_catch")
  NEW_NODE ("gimple_statement_eh_filter")
  NEW_NODE ("gimple_statement_eh_mnt")
  NEW_NODE ("gimple_statement_phi")
  NEW_NODE ("gimple_statement_eh_ctrl")
  NEW_NODE ("gimple_statement_try")
  NEW_NODE ("gimple_statement_wce")
  NEW_NODE ("gimple_statement_asm")
  NEW_NODE ("gimple_statement_omp_critical")
  NEW_NODE ("gimple_statement_omp_for")
  NEW_NODE ("gimple_statement_omp_parallel")
  NEW_NODE ("gimple_statement_omp_task")
  NEW_NODE ("gimple_statement_omp_sections")
  NEW_NODE ("gimple_statement_omp_single")
  NEW_NODE ("gimple_statement_omp_continue")
  NEW_NODE ("gimple_statement_omp_atomic_load")
  NEW_NODE ("gimple_statement_omp_atomic_store")

  #define NEW_EDGE(src, dest) \
  edge = gdl_new_edge (src, dest); \
  gdl_add_edge (graph, edge);

  NEW_EDGE ("gimple_statement_base", "gimple_statement_with_ops_base")
  NEW_EDGE ("gimple_statement_with_ops_base", "gimple_statement_with_ops")
  NEW_EDGE ("gimple_statement_with_ops_base", "gimple_statement_with_memory_ops_base")
  NEW_EDGE ("gimple_statement_with_memory_ops_base", "gimple_statement_with_memory_ops")
  NEW_EDGE ("gimple_statement_with_memory_ops_base", "gimple_statement_call")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_omp")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_bind")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_catch")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_eh_filter")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_eh_mnt")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_phi")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_eh_ctrl")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_try")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_wce")
  NEW_EDGE ("gimple_statement_with_memory_ops_base", "gimple_statement_asm")
  NEW_EDGE ("gimple_statement_omp", "gimple_statement_omp_critical")
  NEW_EDGE ("gimple_statement_omp", "gimple_statement_omp_for")
  NEW_EDGE ("gimple_statement_omp", "gimple_statement_omp_parallel")
  NEW_EDGE ("gimple_statement_omp_parallel", "gimple_statement_omp_task")
  NEW_EDGE ("gimple_statement_omp", "gimple_statement_omp_sections")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_omp_continue")
  NEW_EDGE ("gimple_statement_omp", "gimple_statement_omp_single")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_omp_atomic_load")
  NEW_EDGE ("gimple_statement_base", "gimple_statement_omp_atomic_store")

  gdl_dump_graph (fp, graph);

  fclose (fp);
}

/* Public function to dump the gcc gimple statement structure hierarchy.  */

void
vcg_plugin_dump_gimple_hierarchy (void)
{
  char *fname = "dump-gimple-hierarchy.vcg";

  vcg_plugin_common.init ();

  dump_gimple_hierarchy_to_file (fname);

  vcg_plugin_common.finish ();
}

/* Public function to view the gcc gimple statement structure hierarchy.  */

void
vcg_plugin_view_gimple_hierarchy (void)
{
  char *fname;

  vcg_plugin_common.init ();

  /* Get the temp file name.  */
  fname = vcg_plugin_common.temp_file_name;
  dump_gimple_hierarchy_to_file (fname);
  vcg_plugin_common.show (fname);

  vcg_plugin_common.finish ();
}
