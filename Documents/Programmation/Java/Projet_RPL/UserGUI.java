import java.io.*;
import java.util.StringTokenizer;	//Séparation par défaut : espace, tab ou entrée

class UserGUI{

	public static void parserInput ( StringTokenizer st ) throws Exception // va faire que de l'analyse syntaxique et lexicale, aucun traitement. Il faudra ensuite traiter les cas de pile vide
	{
		String currentString = "";

		while ( st.hasMoreTokens() )
		{
			currentString = st.nextToken(); //pour le sauver

			if( currentString.equals("push") )
			{
				if ( !st.hasMoreTokens() )
				{
					throw new Exception();//on pourrait faire des exceptions custom pour chaque
				}
				//pas besoin de else, on sort déjà en cas d'erreur

				try
				{
					Integer.parseInt(st.nextToken());  // on vérifie qu'après un "push" il y a bien un entier
				}
				catch (NumberFormatException e1)
				{
					throw new Exception();//on pourrait faire des exceptions custom pour chaque
				}
			}	

			else if ( !(currentString.equals("add") || currentString.equals("sub") || currentString.equals("mul") || currentString.equals("div") || currentString.equals("pop")) ) 
				// si c'est pas all good syntaxiquement et lexicalement
				throw new Exception();//on pourrait faire des exceptions custom pour chaque
		}

	}


	public static void calculus ( StringTokenizer st, PileRPL pile ) // ici toutes les opérations sont licites, on les exécute (en vérifiant la sémantique : pile vide...)
	{
		String currentString = "";
		ObjEmp o = null;

		while ( st.hasMoreTokens() )
		{
			currentString = st.nextToken(); //pour le sauver
			
			switch (currentString) {
				case "push" : 
					// on avance encore d'un pour récupérer l'int

					o = new ObjEmp(Integer.parseInt(st.nextToken()));
					try
					{
						pile.push(o);
					}
					catch (IndexOutOfBoundsException e1)
					{
						System.out.println("L'analyse sémantique a fail ! push d'une pile pleine.");
					}
					o = null;
					break;
				case "pop" :
					try
					{
						pile.pop();
					}
					catch (IndexOutOfBoundsException e2)
					{
						System.out.println("L'analyse sémantique a fail ! pop d'une pile vide.");
					}
					break;
				case "add" :
					pile.operations('+'); // pareil que mettre une variable à '+' et appeler la fonction derrière
					break;
				case "sub" :
					pile.operations('-');
					break;
				case "div" :
					pile.operations('/');
					break;
				case "mul" :
					pile.operations('*');
					break;
			}
		}
	}


	//depuis le réseau, vers le réseau
	//en mode enregistrement de log, en mode rejeu de log
	//demander le type de traitement

	public static void main (String[] args)
	{
		BufferedReader entree = new BufferedReader ( new InputStreamReader(System.in));
		PrintStream sortie = new PrintStream (System.out);
		String ligne;
		StringTokenizer st;
		PileRPL pile = new PileRPL(10);

		try
		{
			sortie.println("La pile choisie est de taille 10. \n");
			sortie.println("Commandes possibles : push int // pop // add // mul // sub // div\n");

			sortie.println("\nEtat courant de la pile : \n\n" + pile + "\n");
			sortie.print("? ");
			ligne = entree.readLine();

			while( ligne.length() > 0)
			{
				st = new StringTokenizer(ligne);
				try
				{
					parserInput(st);
					st = null;
					st = new StringTokenizer(ligne); // obligé de le refaire parce que le parser le parcourt intégralement et qu'il n'y a pas moyen de revenir au début de la liste
					calculus(st,pile);
				}
				catch (Exception e1)
				{
					sortie.println("Caractère ou opération invalide !\n");
				}

				sortie.println("\nEtat courant de la pile : \n\n" + pile + "\n");
				sortie.print("? ");
				ligne = entree.readLine();
			}
		}
		catch (IOException e)
		{
			sortie.println("IOException ! ON a pas pu récupérer le flux.\n");
		}
	}

}
