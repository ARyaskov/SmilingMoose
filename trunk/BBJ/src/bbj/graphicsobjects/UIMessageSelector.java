/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;


import bbj.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.awt.Graphics;
/**
 *
 * @author Lemon
 */
public final class UIMessageSelector extends JPanel{
    private Image arrowLeft;
    private Image arrowRight;
    private Image arrowRightInvert;
    private Image arrowLeftInvert;
    private Image messageSmall;
    private Image messageSmall2;
    private Image messageBig;
    private boolean drawInvertLeft;
    private boolean drawInvertRight;
    private boolean drawSelect;
    private boolean drawSelectFill;
    private ArrayList<UIElementInfo> listOfUI;
    private ArrayList<Image> images24px;
    private ArrayList<Image> images48px;
    private ArrayList<String> orderOfTypes;
    private int pointer;
    
    private final int SMALL=1;
    private final int BIG=2;
    private final int SMALL2=3;
    
    private int SHIFTL=1;
    private int SHIFTR=2;

    public class UIElementInfo{
        public int m_height;
        public int m_width;
        public int m_x;
        public int m_y;
        public String m_name = "NULL";
        
        
        public UIElementInfo( int width, int height, int x, int y){

            m_height = height;
            m_width = width;
            m_x = x;
            m_y = y;
        }
        public UIElementInfo( int width, int height, int x, int y, String name){
  
            m_height = height;
            m_width = width;
            m_x = x;
            m_y = y;
            m_name = name;
        }
    }
    
    public UIMessageSelector(){
        listOfUI = new ArrayList<UIElementInfo>();
        images24px = new ArrayList<Image>();
        images48px = new ArrayList<Image>();
        orderOfTypes = new ArrayList<String>();
        orderOfTypes.add("Sync");
        orderOfTypes.add("Async");
        orderOfTypes.add("Reply");
        orderOfTypes.add("Create");
        orderOfTypes.add("Delete");
        
        pointer = 2;
        
        Iterator it48 = orderOfTypes.iterator();
        while(it48.hasNext()){
           images48px.add(new ImageIcon(BBJ.class.getResource
                ("images/48/message"+it48.next()+".png")).getImage());
        }
        Iterator it24 = orderOfTypes.iterator();
        while(it24.hasNext()){
           images24px.add(new ImageIcon(BBJ.class.getResource
                ("images/24/message"+it24.next()+".png")).getImage());
        }
        
        
        drawInvertRight = false;
        drawInvertLeft = false;
        drawSelect = false;
        drawSelectFill = false;
        arrowLeft = 
             new ImageIcon(BBJ.class.getResource("images/16/arrowLeft.png")).getImage();
        arrowRight = 
             new ImageIcon(BBJ.class.getResource("images/16/arrowRight.png")).getImage();
        
        arrowLeftInvert = 
             new ImageIcon(BBJ.class.getResource("images/16/arrowLeftInvert.png")).getImage();
        arrowRightInvert = 
             new ImageIcon(BBJ.class.getResource("images/16/arrowRightInvert.png")).getImage();
        
       
        messageSmall = getTrinityImage(this.SMALL);
        messageBig = getTrinityImage(this.BIG);
        messageSmall2 = getTrinityImage(this.SMALL2);
        
        setSize(new Dimension(messageSmall.getWidth(null)*2+messageBig.getWidth(null)+24,
                messageBig.getHeight(null)+arrowRight.getHeight(null)+24));
       
                
        int distance = 2;
        listOfUI.add(new UIElementInfo(messageSmall.getWidth(null),
                messageSmall.getHeight(null), distance, 0,"messagePrevious"));
        distance += messageSmall.getWidth(null)+10;
        listOfUI.add(new UIElementInfo(messageBig.getWidth(null),
          messageBig.getHeight(null), distance, 0,"messageCurrent"));
        distance += messageBig.getWidth(null) + 10;
        listOfUI.add(new UIElementInfo(messageSmall2.getWidth(null),
          messageSmall.getHeight(null), distance, 0,"messageForward"));
        
                
        int distanceArrow1 = (int) (getSize().getWidth()/2 - arrowLeft.getWidth(null)/2-5);
        int distanceArrow2 = (int) (getSize().getWidth()/2 + arrowLeft.getWidth(null)/2);
       
         listOfUI.add(new UIElementInfo(arrowLeft.getWidth(null),
              arrowLeft.getHeight(null), distanceArrow1, messageBig.getHeight(null)+22,
               "arrowLeft"));

         listOfUI.add(new UIElementInfo(arrowRight.getWidth(null),
              arrowRight.getHeight(null), distanceArrow2, messageBig.getHeight(null)+22,
               "arrowRight"));

         
        this.addMouseListener(new MouseSlot());
    }
    
    public Image getTrinityImage(int type){
        Image result = null;
        switch (type){
            case SMALL: {
             if (pointer>0)
                 result = images24px.get(pointer-1);
             else{
                 result = images24px.get(orderOfTypes.size()-1);
             }
            }break;
            case BIG:{
                result = images48px.get(pointer);
            }break;
            case SMALL2:{
             if (pointer<orderOfTypes.size()-1)
                 result = images24px.get(pointer+1);
             else{
                 result = images24px.get(0);
             }
            }break;
                
        }
        return result;
    }
    
    public void shiftPointer(int type){
        if (type == SHIFTL && pointer>0 )
            pointer--;
        else if (type == SHIFTL){
            pointer = orderOfTypes.size()-1;
        }
        
        if (type == SHIFTR && pointer < orderOfTypes.size()-1)
            pointer++;
        else if (type == SHIFTR){
            pointer = 0;
        }
        
    }
    
    
    @Override
    public void paintComponent(Graphics g){
       
        g.setColor(new Color(255,255,255,255));
        g.fillRect(0, 0, getWidth(), getHeight());
        
       
        g.setColor(new Color(0,0,0,255));
        g.drawRoundRect(0, 0, getWidth()-1, getHeight()-1,10,10);
     
        messageSmall = getTrinityImage(this.SMALL);
        messageBig = getTrinityImage(this.BIG);
        messageSmall2 = getTrinityImage(this.SMALL2);
        
        
        g.setColor(new Color(0,0,0,0));
        g.fillRect(0, 0, getWidth(), getHeight());
    
        g.drawImage(messageSmall, getElementByName("messagePrevious").m_x , 0,null);
        g.drawImage(messageBig, getElementByName("messageCurrent").m_x, 0,null);
        g.drawImage(messageSmall2, getElementByName("messageForward").m_x, 0,null);

        int dist = (int) (getSize().getWidth()/2 - arrowLeft.getWidth(null)/2-5);
        g.setFont(BBJ.messageNameFont);
        g.setColor(new Color(0,0,0,255));
        g.drawString(orderOfTypes.get(pointer), dist, messageBig.getHeight(null)+16);
        

        
        if (drawInvertLeft){
            g.drawImage(arrowLeftInvert, getElementByName("arrowLeft").m_x,
                    getElementByName("arrowLeft").m_y,null);
        } else{
            g.drawImage(arrowLeft, getElementByName("arrowLeft").m_x,
                    getElementByName("arrowLeft").m_y,null);
        }
        if (drawInvertRight){
            g.drawImage(arrowRightInvert, getElementByName("arrowRight").m_x,
                    getElementByName("arrowRight").m_y,null);
        }else{
            g.drawImage(arrowRight, getElementByName("arrowRight").m_x,
                    getElementByName("arrowRight").m_y,null);
        }
        
        if (drawSelectFill){
            g.setColor(new Color(255,255,255,128));
            UIElementInfo curElem = getElementByName("messageCurrent");
            
            g.fillRoundRect(curElem.m_x, curElem.m_y+2,curElem.m_width,
                curElem.m_height, 10, 10);
            g.setColor(new Color(0,0,0,255));
            g.drawRoundRect(curElem.m_x, curElem.m_y+2,curElem.m_width,
                curElem.m_height, 10, 10);
        }
        if (drawSelect){

            UIElementInfo curElem = getElementByName("messageCurrent");
            
            g.setColor(new Color(0,0,0,255));
            g.drawRoundRect(curElem.m_x, curElem.m_y+2,curElem.m_width,
                curElem.m_height, 10, 10);
            
            /* Вариант с линиями
            UIElementInfo curElem = getElementByName("messageCurrent");
            g.setColor(new Color(0,0,0,255));
            g.drawLine(curElem.m_x, curElem.m_y, curElem.m_x,
                    curElem.m_y + curElem.m_height);
            
            g.drawLine(curElem.m_x + curElem.m_width, curElem.m_y, curElem.m_x,
                    curElem.m_y + curElem.m_height);*/
        }
        
        
    }
    
 
    
    public UIElementInfo getElementByName(String s){
       Iterator itr = listOfUI.iterator(); 
       UIElementInfo element;
       while(itr.hasNext()) {
           element = (UIElementInfo)itr.next(); 
           if (element.m_name == null ? s == null : element.m_name.equals(s))
                return element;

       } 
       return null;
    }
    
    class MouseSlot implements MouseListener{
       
        public void mouseClicked(MouseEvent e){

        }
       
        public void mouseEntered(MouseEvent e){

        }

       
        public void mouseExited(MouseEvent e){

        } 
        public void mousePressed(MouseEvent e) {
            if (e.getButton() == MouseEvent.BUTTON1){
               String owner = getOwner(e.getPoint());
               if ("arrowLeft".equals(owner)){
                   drawInvertLeft = true;
                   shiftPointer(SHIFTL);
                   repaint();
               }else if ("arrowRight".equals(owner)){
                   drawInvertRight = true;
                   shiftPointer(SHIFTR);
                   repaint();
               }else if ("messageCurrent".equals(owner)){
                   drawSelectFill = true;
                   repaint();
               }
               
               
            } 

        }

        public void mouseReleased(MouseEvent e) {
            if (e.getButton() == MouseEvent.BUTTON1){
               String owner = getOwner(e.getPoint());
               if (owner == "arrowLeft" && drawInvertLeft == true){
                   drawInvertLeft = false;
                   repaint();
               }else if (owner == "arrowRight" && drawInvertRight == true){
                   drawInvertRight = false;
                   repaint();
               }else{
                   drawSelectFill = false;
                   repaint();
               }
            } 
        } 

    }
    
    public String getOwner(Point p){
       Iterator itr = listOfUI.iterator(); 
       while(itr.hasNext()) {
           UIElementInfo element = (UIElementInfo)itr.next(); 
           if (element.m_x < p.x && element.m_y < p.y
                   && (element.m_x + element.m_width) > p.x 
                   && (element.m_y + element.m_height) > p.y)
           return element.m_name;
       } 
       return null;
    }

}
