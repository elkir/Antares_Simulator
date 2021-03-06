if(NOT MSVC)
	set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS} -Wno-unused-variable")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -Wno-unused-variable")
endif()



set(RTESOLVER_PI
		pointInterieur/pi_alloc_matrice.c
		pointInterieur/pi_alloc_probleme.c
		pointInterieur/pi_armijo.c
		pointInterieur/pi_calculs_utilitaires.c
		pointInterieur/pi_calstaf.c
		pointInterieur/pi_cremat.c
		pointInterieur/pi_cremat_systeme_augmente.c
		pointInterieur/pi_incrementation.c
		pointInterieur/pi_init_transposee.c
		pointInterieur/pi_initxs.c
		pointInterieur/pi_md_equa.c
		pointInterieur/pi_qinit.c
		pointInterieur/pi_quamin.c
		pointInterieur/pi_quamin_calculs.c
		pointInterieur/pi_resolution.c
		pointInterieur/pi_gradient_conjugue.c
		pointInterieur/pi_resolution_systeme_augmente.c
		pointInterieur/pi_reconstruire_matrice_a_resoudre.c
		pointInterieur/pi_restitution_des_resultats.c
		pointInterieur/pi_scaling.c
		pointInterieur/pi_sos1s2.c
		pointInterieur/pi_split_colonnes.c
		pointInterieur/pi_split_contraintes.c
		pointInterieur/pi_constantes_externes.h
		pointInterieur/pi_define.h
		pointInterieur/pi_definition_arguments.h
		pointInterieur/pi_fonctions.h
		pointInterieur/pi_sys.h
	)


set(RTESOLVER_PNE
		pne/pne_ajouter_la_contrainte_de_cout_max.c
		pne/pne_alloc_probleme.c
		pne/pne_allocations_pour_le_postsolve.c
		pne/pne_ameliorer_coefficients.c
		pne/pne_analyse_initiale_knapsack.c
		pne/pne_analyse_initiale_variable_bounds.c
		pne/pne_archiver_la_solution_courante.c
		pne/pne_bb_solve_pb_rlx.c
		pne/pne_calcul_coupes_dintersection.c
		pne/pne_calculer_la_valeur_du_critere.c
		pne/pne_calculer_les_coupes.c
		pne/pne_calculer_les_gomory.c
		pne/pne_calculer_restrictions_bornes.c
		pne/pne_chainage_transposee.c
		pne/pne_choix_des_variables_a_instancier.c
		pne/pne_classer_coeff_contraintes_ordre_decroissant.c
		pne/pne_cliques_controle_avant_resolution.c
		pne/pne_cliques_determination.c
		pne/pne_cliques_violees.c
		pne/pne_clone_spx_noeud_racine.c
		pne/pne_conflict_graph_alloc.c
		pne/pne_conflict_graph_extensions.c
		pne/pne_conflict_graph_fixer_les_voisins_dun_noeud.c
		pne/pne_conflict_graph_fixer_variables.c
		pne/pne_conflict_graph_MAJ.c
		pne/pne_conflict_graph_supprimer_un_noeud.c
		pne/pne_coupe_de_probing.c
		pne/pne_coupes_de_probing_violees.c
		pne/pne_cover_knapsack.c
		pne/pne_cover_knapsack_combinaisons.c
		pne/pne_cover_knapsack_combinaisons_complexes.c
		pne/pne_cover_knapsack_lifting.c
		pne/pne_cover_knapsack_simple.c
		pne/pne_detection_des_contraintes_mixtes.c
		pne/pne_detection_des_gub.c
		pne/pne_detection_des_variables_big_M.c
		pne/pne_determiner_les_variables_fractionnaires.c	
		pne/pne_ecrire_jeu_de_donnees_mps.c
		pne/pne_ecrire_presolved_mps.c
		pne/pne_enlever_tout_petits_termes.c
		pne/pne_enrichir_probleme_avec_coupe.c
		pne/pne_fixation_sur_critere.c
		pne/pne_gomory_negligees.c
		pne/pne_gomory_negligees_violees.c
		pne/pne_gub.c
		pne/pne_heuristique.c
		pne/pne_heuristique_pilotage.c
		pne/pne_heuristique_recherche_en_profondeur.c
		pne/pne_heuristique_resolution_branch_and_bound_reduit.c
		pne/pne_heuristique_RINS.c
		pne/pne_heuristique_utilitaires.c
		pne/pne_heuristique_variables_entieres_fixees.c
		pne/pne_init_pne.c
		pne/pne_inserer_une_contrainte.c
		pne/pne_knapsack_lift_variable_continue.c
		pne/pne_knapsack_negligees.c
		pne/pne_knapsack_negligees_violees.c
		pne/pne_knapsack_sur_coupe.c
		pne/pne_lire_jeu_de_donnees_mps.c
		pne/pne_MIR_agregation.c
		pne/pne_majorant_knapsack.c
		pne/pne_node_dm_A.c
		pne/pne_node_dm_factoriser_matrice.c
		pne/pne_node_dm_resoudre_primal.c
		pne/pne_node_presolve.c
		pne/pne_node_presolve_calculer_bornes_des_contraintes.c
		pne/pne_normaliser_une_coupe.c
		pne/pne_post_probing.c
		pne/pne_postsolve.c
		pne/pne_probing.c
		pne/pne_probing_analyse_liste_de_contraintes.c
		pne/pne_probing_modifier_matrice_des_contraintes.c
		pne/pne_probing_nodepresolve_alloc.c
		pne/pne_probing_nodepresolve_utilitaires.c
		pne/pne_probing_variables_a_instancier.c
		pne/pne_rand.c
		pne/pne_recherche_symetries.c
		pne/pne_recuperer_le_probleme_initial.c
		pne/pne_recuperer_solution_et_critere.c
		pne/pne_reduced_cost_fixing.c
		pne/pne_reduced_cost_fixing_noeud_racine.c
		pne/pne_relance_simplexe_au_noeud_racine.c
		pne/pne_round.c
		pne/pne_solve_pb_rlx_pi.c
		pne/pne_solve_pb_rlx_spx_dual.c
		pne/pne_solve_pb_rlx_spx_primal.c
		pne/pne_solveur.c
		pne/pne_solveur_calculs.c
		pne/pne_solveur_sous_probleme.c
		pne/pne_standalone.c
		pne/pne_strong_branching.c
		pne/pne_strong_branching_classer_le_resultat.c
		pne/pne_trier_les_coupes_calculees.c
		#pne/pne_two_step_mir.c
		pne/mps_define.h
		pne/mps_extern_global.h
		pne/mps_global.h
		pne/pne_constantes_externes.h
		pne/pne_define.h
		pne/pne_definition_arguments.h
		pne/pne_fonctions.h
		pne/pne_sys.h
		pne/pne_cover_knapsack_lifting.c
		pne/pne_knapsack_lift_variable_continue.c
		pne/pne_normaliser_une_coupe.c
		pne/pne_clone_spx_noeud_racine.c
		pne/pne_gomory_negligees.c
		pne/pne_gomory_negligees_violees.c
		pne/pne_knapsack_negligees.c
		pne/pne_knapsack_negligees_violees.c
		pne/pne_knapsack_sur_coupe.c
		pne/pne_coupes_de_probing_violees.c
		pne/pne_cliques_violees.c
		pne/pne_reduced_cost_fixing_noeud_racine.c
		pne/pne_fixation_sur_critere.c
		pne/pne_cliques_controle_avant_resolution.c
		pne/pne_node_presolve.c
		pne/pne_probing_nodepresolve_utilitaires.c
		pne/pne_probing_analyse_liste_de_contraintes.c
		pne/pne_node_presolve_calculer_bornes_des_contraintes.c
		pne/pne_probing_nodepresolve_alloc.c
		pne/pne_heuristique_pilotage.c
		pne/pne_enlever_tout_petits_termes.c
		pne/pne_mise_a_jour_seuil_coupes.c
		pne/pne_reduced_cost_fixing_graphe_de_conflit.c
		pne/pne_presolve_simplifie.c
		pne/pne_contraintes_de_borne_variable_violees.c
		pne/pne_probing_bornes_variables.c
    pne/pne_compacter_matrice_des_contraintes.c
    pne/pne_postsolve_si_presolve_uniquement.c
	)


set(RTESOLVER_LU
		simplexe/lu/lu_allouer_lu.c
		simplexe/lu/lu_calculs_markowitz.c
		simplexe/lu/lu_classement_lignes_colonnes.c
		simplexe/lu/lu_construire_probleme.c
		simplexe/lu/lu_elimination_une_ligne.c
		simplexe/lu/lu_elimination_une_ligne_cas_symetrique.c
		simplexe/lu/lu_elimination_une_ligne_matrice_pleine.c
		simplexe/lu/lu_elimination_une_ligne_turbo.c
		simplexe/lu/lu_factorisation.c
		simplexe/lu/lu_factorisation_calculs.c
		simplexe/lu/lu_inconnues_indeterminees.c
		simplexe/lu/lu_refactorisation.c
		simplexe/lu/lu_refactorisation_de_la_matrice.c
		simplexe/lu/lu_reorganisation_chainages.c
		simplexe/lu/lu_resolution.c
		simplexe/lu/lu_resolution_hyper_creux.c
		simplexe/lu/lu_scaling.c
		simplexe/lu/lu_scan_ligne.c
		simplexe/lu/lu_scan_ligne_cas_symetrique.c
		simplexe/lu/lu_scan_ligne_matrice_pleine.c
		simplexe/lu/lu_scan_super_ligne.c
		simplexe/lu/lu_scan_super_ligne_cas_symetrique.c
		simplexe/lu/lu_selection_pivot.c
		simplexe/lu/lu_selection_pivot_diagonal.c
		simplexe/lu/lu_selection_pivot_matrice_pleine.c
		simplexe/lu/lu_super_lignes_calculs_hashcode.c
		simplexe/lu/lu_super_lignes_creations_et_fusions.c
		simplexe/lu/lu_super_lignes_declenchement.c
		simplexe/lu/lu_super_lignes_detection.c
		simplexe/lu/lu_super_lignes_merge_toutes_super_lignes.c
		simplexe/lu/lu_super_lignes_modifications.c
		simplexe/lu/lu_super_lignes_reallocs.c
		simplexe/lu/lu_switch_markowitz.c
		simplexe/lu/lu_update.c
		simplexe/lu/lu_init_tableaux_null.c
		simplexe/lu/lu_constantes_externes.h
		simplexe/lu/lu_define.h
		simplexe/lu/lu_definition_arguments.h
		simplexe/lu/lu_fonctions.h
		simplexe/lu/lu_sys.h
		simplexe/lu/lu_memoire.h
		simplexe/lu/memstats.c
		simplexe/lu/memstats.h
	)



set(RTESOLVER_SPX
		simplexe/spx_ajouter_coupes.c
		simplexe/spx_allouer_probleme.c
		simplexe/spx_calcul_couts_reduits.c
		simplexe/spx_calcul_du_cout.c
		simplexe/spx_calculer_a_barre_s.c
		simplexe/spx_calculer_b_barre.c
		simplexe/spx_calculer_pi.c
		simplexe/spx_calculer_une_gomory.c
		simplexe/spx_chainage_transposee.c
		simplexe/spx_choix_variable_a_instancier_exploration_rapide_profondeur.c
		simplexe/spx_construire_probleme.c
		simplexe/spx_calcul_coupes_dintersection.c
		simplexe/spx_creation_noeuds_en_exploration_rapide.c
		simplexe/spx_dual_calculer_nbarre.c
		simplexe/spx_dual_choix_variable_entrante.c
		simplexe/spx_dual_choix_variable_sortante.c
		simplexe/spx_dual_comparer_abarre_et_nbarre.c
		simplexe/spx_dual_confirmer_dual_non_borne.c
		simplexe/spx_dual_construire_base_initiale.c
		simplexe/spx_dual_crash_base.c
		simplexe/spx_dual_epurer_la_base.c
		simplexe/spx_dual_phase_1_calculer_v.c
		simplexe/spx_dual_phase_1_choix_variable_entrante.c
		simplexe/spx_dual_phase_1_choix_variable_sortante.c
		simplexe/spx_dual_phase_1_positionner_les_variables.c
		simplexe/spx_dual_phase_1_simplexe.c
		simplexe/spx_dual_simplexe.c
		simplexe/spx_dual_steepest.c
		simplexe/spx_dual_strong_branching.c
		simplexe/spx_dual_strong_branching_GUB.c
		simplexe/spx_ecrire_probleme_mps.c
		simplexe/spx_factoriser_la_base.c
		simplexe/spx_faire_changement_base.c
		simplexe/spx_fixer_x_fonction_de_position.c
		simplexe/spx_gestion_bases_en_exploration_rapide.c
		simplexe/spx_gestion_temps_de_calcul.c
		simplexe/spx_heuristique_arrondis.c
		simplexe/spx_instancier_variable_dans_simplexe.c
		simplexe/spx_mettre_a_jour_la_base.c
		simplexe/spx_modifier_chainage_transposee.c
		simplexe/spx_modifier_couts_ou_second_membre.c
		simplexe/spx_modifier_probleme.c
		simplexe/spx_recuperer_solution.c
		simplexe/spx_recuperer_solution_exploration_rapide_en_profondeur.c
		simplexe/spx_resoudre_by_egal_a.c
		simplexe/spx_resoudre_ub_egal_c.c
		simplexe/spx_sauvegardes_branch_and_bound.c
		simplexe/spx_scaling.c
		simplexe/spx_simplexe.c
		simplexe/spx_simplexe_calculs.c
		simplexe/spx_simplexe_generalise.c
		simplexe/spx_translater_bornes.c
		simplexe/spx_verifier_admissibilite_duale.c
		simplexe/spx_gestion_listes_des_variables_EN_HORS_base.c
		simplexe/spx_calcul_borne_auxiliaire.c
		simplexe/spx_dual_controle_des_bornes_auxiliaires.c
		simplexe/spx_dual_controle_optimalite.c
		simplexe/spx_dual_calculer_nbarre_hyper_creux.c
		simplexe/spx_dual_calculer_nbarrer_standard.c
		simplexe/spx_dual_supprimer_les_bornes_auxilaires.c
		simplexe/spx_verifier_erbmoins1.c
		simplexe/spx_supprimer_une_borne_auxilaire.c
		simplexe/spx_mettre_a_jour_b_barre.c
		simplexe/spx_verifier_a_barre_s.c
		simplexe/spx_calculer_erbmoins1.c
		simplexe/spx_dual_controle_dual_non_borne.c
		simplexe/spx_resolution_de_systeme.c
		simplexe/spx_resolution_de_systeme_transposee.c
		simplexe/spx_appliquer_eta_vecteurs.c
		simplexe/spx_appliquer_eta_vecteurs_transposee.c
		simplexe/spx_init_indicateurs_hypercreux.c
		simplexe/spx_constantes_internes.h
		simplexe/spx_constantes_externes.h
		simplexe/spx_define.h
		simplexe/spx_definition_arguments.h
		simplexe/spx_fonctions.h
		simplexe/spx_memoire.h
		simplexe/spx_sys.h
		simplexe/spx_calcul_du_cout_simplifie.c
		simplexe/spx_calcul_MIR_pour_gomory_et_intersection.c
		simplexe/spx_dual_reconstruire_une_base.c
		simplexe/spx_dual_reconstruire_une_base.c
		simplexe/spx_calculer_erbmoins1_avec_base_complete.c
		simplexe/spx_calculer_b_barre_avec_base_complete.c
		simplexe/spx_verifier_a_barre_s_avec_base_complete.c
		simplexe/spx_calculer_erbmoins1_avec_base_reduite.c
		simplexe/spx_calculer_a_barre_s_avec_base_complete.c
		simplexe/spx_calculer_b_barre_avec_base_reduite.c
		simplexe/spx_verifier_a_barre_s_avec_base_reduite.c
		simplexe/spx_calculer_a_barre_s_avec_base_reduite.c
		simplexe/spx_fixer_x_fonction_de_position_avec_base_complete.c
		simplexe/spx_calcul_couts_reduits_avec_base_complete.c
		simplexe/spx_mettre_a_jour_b_barre_avec_base_reduite.c
		simplexe/spx_calcul_couts_reduits_avec_base_reduite.c
		simplexe/spx_mettre_a_jour_b_barre_avec_base_complete.c
		simplexe/spx_calculer_pi_avec_base_reduite.c
		simplexe/spx_reinit_couts_natif.c
		simplexe/spx_ordonner_contraintes_pour_la_base.c
		simplexe/spx_dual_steepest_resolution_avec_base_complete.c
		simplexe/spx_dual_steepest_resolution_avec_base_reduite.c
		simplexe/spx_calculer_bbarre_hors_base_reduite.c
		simplexe/spx_calculer_pi_avec_base_complete.c
		simplexe/spx_construction_matrice_reduite.c
		simplexe/spx_bruitage_initial_des_couts.c
	)


set(RTESOLVER_MEM
		allocateur/mem_malloc.c
		allocateur/mem_realloc.c
		allocateur/mem_free.c
		allocateur/mem_alloc_super_tableau.c
		allocateur/mem_init_quit.c
		allocateur/mem_sys.h
		allocateur/mem_fonctions.h
		allocateur/mem_allocateur.h
	)


set(RTESOLVER_BB
		branchAndBound/bb_affichages_traces.c
		branchAndBound/bb_alloc_desalloc_probleme.c
		branchAndBound/bb_balayage_en_largeur.c
		branchAndBound/bb_balayage_en_profondeur.c
		branchAndBound/bb_best_first.c
		branchAndBound/bb_branch_and_bound.c
		branchAndBound/bb_branch_and_bound_calculs.c
		branchAndBound/bb_choix_des_variables_a_instancier.c
		branchAndBound/bb_controler_les_coupes_non_prises_en_compte.c
		branchAndBound/bb_creation_noeud.c
		branchAndBound/bb_creer_les_noeuds_fils.c
		branchAndBound/bb_eliminer_les_noeuds_sous_optimaux.c
		branchAndBound/bb_evaluer_en_profondeur_critiques.c
		branchAndBound/bb_evaluer_fils_du_meilleur_minorant.c
		branchAndBound/bb_exploration_rapide_en_profondeur.c
		branchAndBound/bb_inserer_les_coupes.c
		branchAndBound/bb_nettoyer_arbre.c
		branchAndBound/bb_nettoyer_les_coupes.c
		branchAndBound/bb_rechercher_le_meilleur_minorant.c
		branchAndBound/bb_rechercher_le_noeud_avec_meilleur_ratio_fractionnaire.c
		branchAndBound/bb_rechercher_le_noeud_le_moins_fractionnaire.c
		branchAndBound/bb_resoudre_le_probleme_relaxe.c
		branchAndBound/bb_stocker_les_coupes_du_noeud.c
		branchAndBound/bb_supprimer_les_descendants_dun_noeud.c
		branchAndBound/bb_define.h
		branchAndBound/bb_fonctions.h
		branchAndBound/bb_sys.h
	)

set(RTESOLVER_PRS
		presolve/prs_DM.c
		presolve/prs_DM_A.c
		presolve/prs_DM_factoriser_matrice.c
		presolve/prs_DM_resoudre_dual.c
		presolve/prs_DM_resoudre_primal.c
		presolve/prs_DM_resoudre_systeme_transpose.c
		presolve/prs_allocations.c
		presolve/prs_alloc_reductions.c
		presolve/prs_ameliorer_bornes.c
		presolve/prs_ameliorer_coefficients.c
		presolve/prs_ameliorer_contraintes_de_bornes_variables.c
		presolve/prs_calcul_borne_sur_variable_avec_une_contrainte.c
		presolve/prs_calcul_borne_sur_variable_duale_avec_une_variable.c
		presolve/prs_calculer_bornes_contraintes.c
		presolve/prs_colonnes_colineaires.c
		presolve/prs_combinaisons_de_contraintes.c
		presolve/prs_contraintes_colineaires.c
		presolve/prs_contraintes_inactives.c
		presolve/prs_contruire_graphe_DIMACS.c
		presolve/prs_desactiver_contrainte.c
		presolve/prs_determiner_le_type_de_borne_pour_dual.c
		presolve/prs_enlever_contraintes_inactives.c
		presolve/prs_fixer_une_variable_a_une_valeur.c
		presolve/prs_fixer_variables_sur_critere.c
		presolve/prs_maj_variable_duale.c
		presolve/prs_mettre_a_jour_bornes_des_variables.c
		presolve/prs_mettre_a_jour_bornes_des_variables_duales.c
		presolve/prs_presolve.c
		presolve/prs_singleton_colonne.c
		presolve/prs_singleton_ligne.c
		presolve/prs_substituer_variables.c
		presolve/prs_substituer_variables_non_bornees.c
		presolve/prs_supprimer_contraintes_sans_variables.c
		presolve/prs_variable_probing.c
		presolve/prs_variables_hors_contraintes.c
		presolve/prs_variables_duales_ameliorer_bornes.c
		presolve/prs_variables_duales_et_couts_reduits.c
		presolve/prs_variables_duales_non_bornees.c
		presolve/prs_variables_non_bornees.c
		presolve/prs_define.h
		presolve/prs_fonctions.h
		presolve/prs_sys.h
	)
	
set(SRC_SOLVER
	${RTESOLVER_SPX}
	${RTESOLVER_LU}
	${RTESOLVER_PRS}
	${RTESOLVER_PNE}
	${RTESOLVER_BB}
	${RTESOLVER_PI}
	${RTESOLVER_MEM}
)

add_library(libsolver_antares  ${SRC_SOLVER})
target_include_directories(libsolver_antares PUBLIC .)
target_include_directories(libsolver_antares PUBLIC "branchAndBound")
target_include_directories(libsolver_antares PUBLIC "simplexe/lu")
target_include_directories(libsolver_antares PUBLIC "presolve")
target_include_directories(libsolver_antares PUBLIC "simplexe")
target_include_directories(libsolver_antares PUBLIC "pne")
target_include_directories(libsolver_antares PUBLIC "branchAndBound")
target_include_directories(libsolver_antares PUBLIC "allocateur")
target_include_directories(libsolver_antares PUBLIC "pointInterieur")

add_library(libsolver_antares-swap  ${SRC_SOLVER})
target_include_directories(libsolver_antares-swap PUBLIC .)

target_include_directories(libsolver_antares-swap PUBLIC "branchAndBound")
target_include_directories(libsolver_antares-swap PUBLIC "simplexe/lu")
target_include_directories(libsolver_antares-swap PUBLIC "presolve")
target_include_directories(libsolver_antares-swap PUBLIC "simplexe")
target_include_directories(libsolver_antares-swap PUBLIC "pne")
target_include_directories(libsolver_antares-swap PUBLIC "branchAndBound")
target_include_directories(libsolver_antares-swap PUBLIC "allocateur")
target_include_directories(libsolver_antares-swap PUBLIC "pointInterieur")


set_target_properties(libsolver_antares-swap
	PROPERTIES COMPILE_FLAGS " -DANTARES_SWAP_SUPPORT=1")
