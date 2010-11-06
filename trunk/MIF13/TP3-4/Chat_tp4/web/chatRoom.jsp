<%
    //---> ne pas utiliser d'include, sa ne fonctionne pas sinon ! :p
    //Pour �viter que l'on se connecte, sans m�me avoir de session (php like)
    String sessionNom = (String) request.getSession(false).getAttribute("nom");
    if (sessionNom == null) response.sendRedirect("connexion.html");

%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
   "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">


<html>
    <head>
        
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />

        <title>Chat-Room</title>

        <link rel="stylesheet" type="text/css" href="css/template.css"  />

        <script type="text/javascript" src="js/ajax.js"></script>
        <script type="text/javascript" src="js/actions.js"></script>

    </head>

    <body onLoad="recupererMessages()">

        <div >
            <h2 class="titre">___ooo(O.O)ooo___</h2>
        </div>

        <form  id="deconnexion" method="GET" action="Logout">
            <div>
                <input type="submit" name="deconnexion" value="D�connexion" />
            </div>
        </form>

        <div id="listeMessages">
            <div id="messages">
            </div>
            <a name="dernierMessage" />
        </div>


        <div id="saisie">
            <fieldset>
                <legend>Message � envoyer</legend>
                <form action="" onsubmit="stockerMessage('texte')">
                      <input type="text" id="texte"/>
                      <input type="submit" />
                </form>
            </fieldset>
        </div>

    </body>
</html>