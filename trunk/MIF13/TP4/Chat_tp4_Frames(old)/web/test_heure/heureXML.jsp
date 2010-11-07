<%-- Cr�e le code xml de l'heure, qui sera ins�r� dans une page xml--%>

<%@page import="java.util.Locale"%>
<%@page import="java.util.GregorianCalendar"%>
<%@page import="java.util.Calendar"%>
<%@page import="java.util.Date"%>


<%

//Cr�ation d'un calenrier G�orgien pour la France
Calendar calendar = new GregorianCalendar(new Locale("Fr"));
Date trialTime = new Date();

calendar.setTime(trialTime);

%>

<date>
    <heure><%=calendar.get(Calendar.HOUR_OF_DAY)%>:</heure>
    <min><%=calendar.get(Calendar.MINUTE)%>:</min>
    <sec><%=calendar.get(Calendar.SECOND)%></sec>
</date>
