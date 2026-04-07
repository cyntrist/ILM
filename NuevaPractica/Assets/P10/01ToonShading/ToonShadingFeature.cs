using System;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;
using UnityEngine.Rendering.RenderGraphModule;

public class ToonShadingFeature : ScriptableRendererFeature
{
    [SerializeField] [Range(0, 10)] private int factor = 7;
    private ToonShadingPass m_ToonShadingPass;

    public override void Create()
    {
        m_ToonShadingPass.renderPassEvent = RenderPassEvent.AfterRenderingPostProcessing;
    }

    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        m_ToonShadingPass.Setup(factor);
        renderer.EnqueuePass(m_ToonShadingPass);
    }
}
