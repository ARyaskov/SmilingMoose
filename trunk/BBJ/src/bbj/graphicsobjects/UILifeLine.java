
package bbj.graphicsobjects;

import bbj.graphicsobjects.*;
import bbj.virtualobjects.*;
import bbj.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;
import javax.swing.*;

/**
 * Абстрактный класс линии жизни
 * @author Lemon
 */
abstract public class UILifeLine extends SceneItem{
    
    /** Флаг завершенности линии жизни. */
    protected boolean m_isEnded;
    
    /** Координата текста по Х */
    protected int m_textCoordX;
    
    /** Координата текста по У */
    protected int m_textCoordY;
    
    /** Контейнер входящих сообщений. */
    public ArrayList<UIMessage>m_inbox;
    
    /** Контейнер исходящих сообщений. */
    public ArrayList<UIMessage>m_outbox;
    
    public int dotCoord;
    
    /** Длина ЛЖ*/
    private int m_length;
    
    
    /** Внутреннее меню. */
    PopupMenu m_menu;
    MenuItem m_stop;
    
    public void removeMessages(){
        Iterator<UIMessage> i = m_inbox.iterator();
        Scene s =  bbj.BBJ.app.getScene();
        while(i.hasNext()){
            
            UIMessage buf = i.next();
            
            if (buf.m_focusReceiver!=null){
                s.remove(buf.m_focusReceiver);
                s.getGraphicsObjects().remove(buf.m_focusReceiver);
            }
                       
            if (buf.m_focusSender!=null){
               s.remove(buf.m_focusSender);
               s.getGraphicsObjects().remove(buf.m_focusSender);
            }
                
            s.remove(buf);
            s.getGraphicsObjects().remove(buf);
            buf = null;
        }
        
        m_inbox.clear();
        
        i = m_outbox.iterator();
        
        while(i.hasNext()){
            
            UIMessage buf = i.next();
            
            if (buf.m_focusReceiver!=null){
                s.remove(buf.m_focusReceiver);
                s.getGraphicsObjects().remove(buf.m_focusReceiver);
            }
                       
            if (buf.m_focusSender!=null){
               s.remove(buf.m_focusSender);
               s.getGraphicsObjects().remove(buf.m_focusSender);
            }
            
            s.remove(buf);
            s.getGraphicsObjects().remove(buf);
            buf = null;
        }
        
        m_outbox.clear();
    }

    protected void fillData(int x, int y) {
        this.defX = x;
        this.defY = 50;
        //this.w = 120;
        //this.h = 300;

        defW=120;
        defH=300;
        
        applyScale(getGraphics());
               
        m_length = this.h-20 - this.y+50;
        
        setBounds(x, y, w, h);
        this.m_isEdit = false;
        this.m_isSelected = false;
        
        m_inbox = new ArrayList<UIMessage>();
        
        m_outbox = new ArrayList<UIMessage>();
        
    }
    
    /**
     * Получить длину ЛЖ
     * @return Длина ЛЖ
     */
    public int getLength(){
        return m_length;
    }
    
    /**
     * Задать длину ЛЖ
     * @param length Новая длина
     */
    public void setLength(int length){
        m_length = length;
        this.defH = m_length + zoom(20) - this.y+zoom(50);
    }
    
    /**
     * Сделать линию жизни завершенной
     * @param flag Значение флага
     */
    public void setEnded(boolean flag){
        m_isEnded = flag;
    }
    
    /**
     * Узнать завершена ли линия жизни
     * @return Результат
     */
    public boolean isEnded(){
        return m_isEnded;
    }
    
    /**
     * Отрисивка линии жизни
     * @param g Компонент, на котором рисуем
     */
    @Override
    public void paint(Graphics g){
          
        super.paint(g);
        
        applyScale(g);
        
        Graphics2D g2 = (Graphics2D)g;
    
        specificPaint(g2);
        
        this.setBounds(this.x,this.y,w+10,h-20);
        
        dotCoord = this.y + h-zoom(20);
        
//        g2.setStroke(new BasicStroke(3.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
//                1.0f,new float[]{8.0f,6.0f},0.0f));
//        g2.drawLine(68, 60, 68, 280);           
        
        g2.setStroke(new BasicStroke(1));
       
        if (m_isEnded){
            g.drawLine(x+zoom(40), this.h-zoom(40), x+zoom(80), this.h);
            g.drawLine(x+zoom(40), this.h, x+zoom(80), this.h-zoom(40));
        }
                 
        g2.setStroke(new BasicStroke(1.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
                1.0f,new float[]{8.0f,4.0f},0.0f));
        
        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
                
        g2.drawLine(x+zoom(60), y+zoom(50), x+zoom(60), this.h-20);
        
        m_length = this.h-zoom(20) - this.y+zoom(50);
        
        // Разбиваем текст на массив символов
        char [] drawedText = m_text.toCharArray();
        char [] dots = {'.','.','.'};
        
        g.drawChars(drawedText, 0, java.lang.Math.min(13, m_text.length()), m_textCoordX, m_textCoordY);
        
        if (m_text.length() >= 14)
            g.drawChars(dots, 0, 3, m_textCoordX+zoom(90), m_textCoordY);

        // Рисуем кружок для изменения размера
        if (m_isSelected){
            g2.setStroke(new BasicStroke(1));
            g2.drawOval(x +zoom(57), this.h-zoom(23), zoom(6), zoom(6));
        }
        
        if (m_isEdit) 
            f.repaint();
    }
    
    abstract public void specificPaint(Graphics g);
}
