/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 16:57:54 by rfulop            #+#    #+#             */
/*   Updated: 2017/08/01 02:02:06 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

***** Wesh les gros *****

Je fais un README.md pour communiquer les infos INDISPENSABLES pour avancer.

A la racine d'"asm", on compile tous les *.c et *.h, avec la libft (j'ai pris la mienne parce qu'elle compile mon printf, c'est un detail, on changera ca plus tard).
Le binaire s'execute avec un .s dans le dossier "tests".

ATM :
	Je suis entrain de faire un compteur d'octets fonctionnel. Pour le moment, je pars du principe que ce qui est envoye est valide.
	MAJ : LE COMPTEUR D'OCTETS EST FONCTIONNEL.
		LA LISTE CHAINEE RECUPERANT LES POSITIONS DES LABELS EST IMPLEMENTEE.
	On va pouvoir passer aux choses serieuses -> convertir les donnees asm en bytecode.
	
FOR :
	Le compilateur va d'abord lire une premiere fois le fichier afin de recuperer les labels et leur position en octets a partir de l'octet 0 (qui est le debut des instructions asm). Pour le moment, ce qui est au dessus des instructions en asm est ignore, afin de ne pas trop en chier pour verifier les sorties en hexa.

SOON:
	Lorsque le compteur sera fonctionnel, il est, pour le moment, nous stockons les noms des labels dans une liste chainee, qui ressemble a un truc comme ca:

	typedef struct s_labs
	{
		char			*name;
		int				*pos;
		struct s_labs	*next;
	}					t_labs

	Elle est elle meme contenu dans une structure env, qui pointe aussi sur un int comptenant le no;nre d'octets.
	Je ne vois pas de raison d'avoir une autre structure pour l'asm, ni meme de stocker d'autres donnees. On ne va rien stocker d'autre que le nom des labels et leurs positions.
	Le compilateur va lire, ligne par ligne, le .s et convertir les instructions en char, short et int, selon ce que l'on converti.

RAPPEL:
	OPCODE: 1 octet.
	OCP : 1 octet.
	REGISTRE : 1 octet.
	INDEX : 2 octets.
	DIRECT : 2 octets pour les adresses memoires (Instructions zjmp, ldi, sti, fork, ldi, lfork)
			 4 octets pour les entiers (instructions live, ld, and, or, xor, lld)

VDM:
	En ce qui concerne le check, il pourrait intervenir a chaque ligne pendant le comptage des octets, au premier passage du gnl et serait ignore la seconde fois, lors de la convertion de l'asm.
	Pour l'ecriture, j'imagine qu'a la suite du comptage d'octets et de la recuperation des labels, on pourra creer le fichier, et ft_put/char/str_fd directement dedans.
	Je ne suis pas encore certain de tout cela. Toute remarque est bienvienue a ce sujet.

INFOS EN VRAC:
	Tout le code est quasi dans un seul fichier, je reglerai ca plus tard. Le lecteur est libre de mettre le code au propre !
	J'ai la flemme de faire un Makefile.
	Quand est ce qu'on boit une biere ?
	Sisi la famille.
