using System;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;
using UnityEngine.Rendering.RenderGraphModule;

public class BlancoYNegroFeature : ScriptableRendererFeature
{
    private BlancoYNegroPass m_BlancoYNegroPass;

    [SerializeField]
    private RenderPassEvent _renderPassEvent;

    [SerializeField] [Range(0.0f, 1.0f)] private float factor = 0.5f;

    private Material material;

    // se llama a esto cada vez que se cambia algo (incluyendo en su creacion)
    public override void Create()
    {
        m_BlancoYNegroPass = new BlancoYNegroPass();
        m_BlancoYNegroPass.renderPassEvent = RenderPassEvent.AfterRenderingPostProcessing; // tras post-procesado

        Shader shader = Shader.Find("Hidden/BlancoYNegro");
        material = CoreUtils.CreateEngineMaterial(shader);
        //CoreUtils.Destroy(material);
    }

    protected override void Dispose(bool disposing)
    {
        //base.Dispose(disposing);
    }

    // se llama una vez por frame
    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        m_BlancoYNegroPass.Setup(factor, material);
        renderer.EnqueuePass(m_BlancoYNegroPass);
    }
}
