<%-- R�ception et m�morisation des messages envoy�s par POST Affichage des messages--%>

<%@page import="Gestion.Message"%>

<jsp:useBean id="bean" scope="application" class="Gestion.GestionMessages"/>

<%
    String messageRecu = request.getParameter("message");

    if(messageRecu != null)
        bean.ajouterMessage(new Message(messageRecu, (String) session.getAttribute("nom")));
%>

<jsp:forward page="affichage.jsp"/>