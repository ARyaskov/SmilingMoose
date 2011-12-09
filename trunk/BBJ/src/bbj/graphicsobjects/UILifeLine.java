
package bbj.graphicsobjects;

import bbj.graphicsobjects.*;
import bbj.virtualobjects.*;
import bbj.*;
import java.awt.*;
import java.util.ArrayList;
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

    protected void fillData(int x, int y) {
        this.x = x;
        this.y = 50;
        this.w = 120;
        this.h = 300;
        
        setBounds(x, y, w, h);
        this.m_isEdit = false;
        this.m_isSelected = false;
        
        m_inbox = new ArrayList<UIMessage>();
        
        m_outbox = new ArrayList<UIMessage>();
        
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
    public void paint(Graphics g){
                      
        Graphics2D g2 = (Graphics2D)g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, BBJ.qltAntialiasing);
        g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, BBJ.qltTextAntialiasing);
        g2.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION, BBJ.qltAlphaInterpolation);
        g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, BBJ.qltInterpolation);
        g2.setRenderingHint(RenderingHints.KEY_RENDERING, BBJ.qltRender);  

        
        specificPaint(g2);
        
        this.setBounds(this.x,this.y,w+10,h-20);
        
//        g2.setStroke(new BasicStroke(3.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
//                1.0f,new float[]{8.0f,6.0f},0.0f));
//        g2.drawLine(68, 60, 68, 280);           
        
        g2.setStroke(new BasicStroke(1));
       
        if (m_isEnded){
            g.drawLine(x+40, this.h-40, x+80, this.h);
            g.drawLine(x+40, this.h, x+80, this.h-40);
        }
                 
        g2.setStroke(new BasicStroke(1.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
                1.0f,new float[]{8.0f,4.0f},0.0f));
        
        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g2.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g2.setColor(Color.black);
                
        g2.drawLine(x+60, y+50, x+60, this.h-20);
        
        // Разбиваем текст на массив символов
        char [] drawedText = m_text.toCharArray();
        char [] dots = {'.','.','.'};
        
        g.drawChars(drawedText, 0, java.lang.Math.min(13, m_text.length()), m_textCoordX, m_textCoordY);
        
        if (m_text.length() >= 14)
            g.drawChars(dots, 0, 3, m_textCoordX+90, m_textCoordY);

        // Рисуем кружок для изменения размера
        if (m_isSelected){
            g2.setStroke(new BasicStroke(1));
            g2.drawOval(x +57, this.h-23, 6, 6);
        }
        
        if (m_isEdit) 
            f.repaint();
    }
    
    abstract public void specificPaint(Graphics g);
}
