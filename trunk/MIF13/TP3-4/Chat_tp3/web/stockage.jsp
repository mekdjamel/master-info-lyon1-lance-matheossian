<%-- R�ception et m�morisation des messages envoy�s par POST Affichage des messages--%>

<%@page import="Gestion.Message"%>
<jsp:useBean id="gestion" scope="application" class="Gestion.GestionMessages"/>

<%
    String messageRecu = request.getParameter("message");

    if(messageRecu != null && !messageRecu.isEmpty()){

        //ajout � la liste
        gestion.ajouterMessage(new Message((String) session.getAttribute("nom"),messageRecu));

    }
    
%>