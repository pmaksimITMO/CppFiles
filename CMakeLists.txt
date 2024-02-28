cmake_minimum_required(VERSION 3.20)
project(CppFiles)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CppFiles
#        "evm/easy.cpp"
#        "evm/cache.cpp"
#        "LOSH2021/heavy-light decomposition.cpp"
#        "LOSH2021/suff-mas.cpp"
#        "Yandex trainings 3.0/Beautiful_String.cpp"
#        ALGORITHMS/SegTree/RMQ.cpp
#        ALGORITHMS/SegTree/PermutationOnSeg.cpp
#        "Yandex trainings 3.0/ContestBackend_A.cpp"
#        "Yandex trainings 3.0/ContestBackend_B.cpp"
#        "Yandex trainings 3.0/ContestBackend_C.cpp"
#        "Yandex trainings 3.0/ContestBackend_D.cpp"
#        "Yandex trainings 3.0/ContestBackend_stupid_solve.cpp"
#        DMlabs/Test2.cpp
#        CppCourse/substring.cpp
#        DMlabs/Test3.cpp
#        CppCourse/matrix/main.cpp
#        CppCourse/matrix/matrix_practise.h
#        CppCourse/matrix/matrix.h
#        CppCourse/vector/test.cpp CppCourse/vector/vector.h
#        DMlabs/dm_lab_avt.cpp
#        CppCourse/bigint/big_integer.h CppCourse/bigint/big_integer.cpp
#        ALGORITHMS/lca/min-cost-lca.cpp
#        ALGORITHMS/lca/simple-lca.cpp ALGORITHMS/sparse-table/simple-sparse-table.cpp
#        ALGORITHMS/SegTree/mass-operations.cpp
#        ALGORITHMS/treap/treap-reverse.cpp
#        ALGORITHMS/treap/treap-kth-max.cpp
#        ALGORITHMS/treap/Swapper.cpp
#        ALGORITHMS/SegTree/RMQ_reverse.cpp
#        ALGORITHMS/SegTree/SegTree_2D.cpp
#        ALGORITHMS/SegTree/Fenwick.cpp
#        ALGORITHMS/dfs_mst/A.top_sort.cpp
#        ALGORITHMS/dfs_mst/B_bridges.cpp
#        ALGORITHMS/dfs_mst/C_articulation_points.cpp
#        ALGORITHMS/dfs_mst/D_edge_connectivity.cpp
#        ALGORITHMS/dfs_mst/E_point_connectivity.cpp
#        ALGORITHMS/dfs_mst/F_condensation.cpp
#        ALGORITHMS/dfs_mst/H_avia.cpp
#        ALGORITHMS/dfs_mst/I_MST_PRIM.cpp
#        ALGORITHMS/dfs_mst/J_MST_Kraskal.cpp
#        ALGORITHMS/dfs_mst/G_2SAT.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/A_Floyd.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/B_Deikstra.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/C_NegCycle.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/D_K_length_paths.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/E_Ford_Bellman.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/F_lost_kefir.cpp
#        DMlabs/2sem/A_gamil_cycle.cpp
#        DMlabs/2sem/B_gamil_cycle2.cpp
#        DMlabs/2sem/E_prufer_code.cpp
#        DMlabs/2sem/F_repair_tree_using_prufer_code.cpp
#        DMlabs/2sem/C_interactive.cpp
#        DMlabs/2sem/D_tournir_gamil_cycle.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/H_easy_game.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/I_retroanalyz.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/J_Grandy_function.cpp
#        ALGORITHMS/shortestPaths_gamesTheory/K_drovosek.cpp
#        DMlabs/3sem/test_graphs.cpp
#        DMlabs/3sem/Matroids/A.cpp
#        DMlabs/3sem/Matroids/B.cpp
#        DMlabs/3sem/Matroids/C.cpp
#        DMlabs/3sem/Matroids/D.cpp
#        DMlabs/3sem/Matroids/E.cpp
#        DMlabs/3sem/Matroids/F.cpp
#        ALGORITHMS/Strings/Substrings_equals.cpp
#        ALGORITHMS/Strings/Prefix_function.cpp
#        ALGORITHMS/Strings/Z_function.cpp
#        ALGORITHMS/Strings/All_Meetings_Substring.cpp
#        ALGORITHMS/Strings/Period.cpp
#        ALGORITHMS/Strings/Maximum_common_substring.cpp
#        ALGORITHMS/Strings/Axo-Corasic.cpp
#        ALGORITHMS/Strings/SufMass.cpp
#        ALGORITHMS/Strings/SufMass_Cnt_Diff_Substrings.cpp
#        ALGORITHMS/Strings/SufMass_kth_cycle_shift.cpp
#        ALGORITHMS/Strings/SufMass_common_substring_2_strings.cpp
#        ALGORITHMS/Strings/SufMass_Multiple_Search.cpp
#        ALGORITHMS/Strings/Axo-Corasic_first_last_meet.cpp
#        ITMO_ICPC/IntroContest/A.cpp
#        ITMO_ICPC/IntroContest/B.cpp
#        ITMO_ICPC/IntroContest/C.cpp
#        ITMO_ICPC/IntroContest/D.cpp
#        ITMO_ICPC/IntroContest/F.cpp
#        ITMO_ICPC/IntroContest/G.cpp
#        ITMO_ICPC/IntroContest/I.cpp
#        ALGORITHMS/parsoch/parsoch.cpp
#        ALGORITHMS/parsoch/birthday.cpp
#        ALGORITHMS/parsoch/nlo.cpp
        ALGORITHMS/parsoch/max_parsoch.cpp
#        ALGORITHMS/parsoch/domino.cpp
#        ALGORITHMS/parsoch/segments.cpp
#        ALGORITHMS/parsoch/dragons.cpp
        )
