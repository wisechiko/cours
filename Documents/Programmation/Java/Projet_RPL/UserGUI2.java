import java.io.*;
import java.util.StringTokenizer;	//Séparation par défaut : espace, tab ou entrée

class UserGUI2{


	public static boolean isOperande ( String s ) // c'est une lib, donc une classe statique
	{
		if ( s.equals("+") || s.equals("-") || s.equals("*") || s.equals("/") )
			return true;
		else
			return false;
	}


	//Ce parser prends en input un StringTokenizer et renvoie 2 String[] contenant opérations et opérandes
	//avec des Map<> on pourrait s'éviter de travailler avec que des String et de faire de multiples conversions inutiles
	public static String[][] parserDuPauvre ( StringTokenizer st ) throws Exception // c'est une lib, donc une classe statique
	{

		int size = st.countTokens();
		if ( (size%2) == 0) //on règle ici le problème des opérations de taille paire
			throw new Exception();

		String[][] outbuffer = new String[2][];
		//La première ligne contiendra les opérandes et la seconde les opérateurs
		//Les définir comme ceci permet que si l'on ajoute au delà de la taille on soulèvera une Exception.
		//La syntaxe du calcul est assurée de cette façon
		outbuffer[0] = new String [ size/2 + 1 ];
		outbuffer[1] = new String [ size/2 ];

		String currentString = "";
		int i = 0;
		int j = 0;
		boolean operations = false;

		while( st.hasMoreTokens() )
		{

			currentString = st.nextToken(); //pour le sauver

			if (!operations)
			{
				//ici se fait le test de type ; si c'est pas un int, ça catch
				try
				{
					Integer.parseInt(currentString); //seul moyen pour trouver le type ?
					outbuffer[0][i] = currentString;
					i++; //pourrait être condensé en une ligne ?
				}

				catch (NumberFormatException e1)
				{
					//pour régler le premier cas... ça fait 2 fois le même code
					//mais y'a pas de StringTokenizer.previousToken()..

					if ( isOperande(currentString) )
					{
						outbuffer[1][0] = currentString;
						j=1; //comme c'est sûr que c'est le premier cas, autant pas j++
					}
					else
					{
						throw new Exception();	
					}
					operations = true;
				}


			}
			else
			{
				if ( isOperande(currentString) )
				{
					outbuffer[1][j] = currentString;
					j++; //pourrait être condensé en une ligne ?
				}
				else
				{
					throw new Exception();
				}
			}
		}

		return outbuffer;
	}


	public static void start()
	{

		BufferedReader entree = new BufferedReader ( new InputStreamReader( System.in ) );
		String ligne;
		PrintStream sortie = new PrintStream ( System.out );
		StringTokenizer st;
		PileRPL pile;
		ObjEmp o;
		String[][] inputTraite = new String [2] [1]; // pourquoi 1 ?????
		int i=0;

		try
		{

			System.out.println("\nVeuillez écrire votre calcul en notation postfixée:\n");
			ligne = entree.readLine();

			while( ligne.length() > 0 )
			{

				st = new StringTokenizer( ligne );

				try 
				{
					inputTraite = parserDuPauvre ( st );
					pile = new PileRPL(inputTraite[0].length);

					for(i=0;i<inputTraite[0].length;i++)
					{
						o = new ObjEmp(Integer.parseInt(inputTraite[0][i]));
						pile.push(o);
						// passer à null dit au garbage collector de venir libérer cette mémoire
						// qu'on instancie pas (new) des nouvelles piles à l'infini
						// Sauf si c'est fait tout seul ?
						o = null;
					}
					for(i=0;i<inputTraite[1].length;i++)
					{
						pile.operations(inputTraite[1][i].charAt(0));
					}
					sortie.println("Résultat : " + pile);
				}

				catch (Exception e)
				{
					sortie.println("\n Opération ou caractère invalide ! Le parser a gueulé.");
				}

				sortie.println("\n--------------------------------------\n");
				sortie.println("Veuillez écrire votre nouveau calcul :\n");

				// passer à null dit au garbage collector de venir libérer cette mémoire
				// qu'on instancie pas (new) des nouvelles piles à l'infini
				//Sauf si c'est fait tout seul ?
				st = null ;
				pile = null ;

				ligne = entree.readLine();
			}
		}

		catch (IOException e1)
		{
			System.out.println("IOException. Dafuq ?");
		}
	}
}
