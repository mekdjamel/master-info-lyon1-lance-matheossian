<%--
    Cette page n'est plus atteinte ! C'�tait la premi�re partie du TP.
--%>

<%@page language="java"%>


<%@ taglib uri="http://struts.apache.org/tags-bean" prefix="bean" %>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Validation formulaire</title>
    </head>
    <body>
        <h2>Vos donn�es</h2>
        <div>
            Votre nom : <bean:write name="Profil" property="nom" /> <br/>
            Votre sexe : <bean:write name="Profil" property="sexe" />
        </div>
    </body>
</html>
